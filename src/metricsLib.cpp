#include "../include/metricsLib.hpp"
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
namespace metrics {
    void MetricStorage::addMetric(MetricPtr metric) {
        mutexStorage.lock();
        std::string nameMetric = metric->getName();
        this->storage_[nameMetric] = metric;
        mutexStorage.unlock();
    }
    
    std::map <std::string, MetricPtr>& MetricStorage::getStorage() {
        return storage_;
    }

    MetricCollector::MetricCollector(std::string filename, StorageMetricPtr storage) {
        filename_ = filename;
        storagePtr_ = storage;
        workThread_ = std::thread(&MetricCollector::workThreadFunc, this);
    }

    void MetricCollector::workThreadFunc() {
        while (true) {
            MetricMessage metricsToWrite;
            {
                std::unique_lock <std::mutex> lock(mutexQueue);
                queueCV.wait(lock, [&]{
                    return !metricsQueue.empty() || finished.load();
                });
                if (metricsQueue.empty() || finished.load()) {
                    break;
                } else {
                    metricsToWrite = metricsQueue.front();
                    metricsQueue.pop();
                }
            }
            writeToFile(metricsToWrite);
        }
    }

    void MetricCollector::writeToFile(MetricMessage metricMSG) {
        auto now = std::chrono::system_clock::now(); 
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss; 
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S"); 
        ss << "." << std::setfill('0') << std::setw(3) << now_ms.count() << " ";

        for (const auto& [name, value] : metricMSG) {
            ss << "\"" << name << "\" " << std::fixed << std::setprecision(2) << value << " ";
        }
        ss << std::endl;

        std::ofstream outfile(filename_, std::ios::app);
        outfile << ss.str(); 
        outfile.close(); 
    }

    void MetricCollector::collect() {
        std::lock_guard<std::mutex> lock(mutexCollect);
        MetricMessage values; 

        for (auto& [name, metric] : storagePtr_->getStorage()) {
            values[name] = metric->getValueAsString();
        }

        mutexQueue.lock();
        metricsQueue.push(values);
        mutexQueue.unlock();

        queueCV.notify_one();
    }

    MetricCollector::~MetricCollector() {
        finished.store(true);
        queueCV.notify_one();
        workThread_.join();
    }
}
