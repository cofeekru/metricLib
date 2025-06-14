#pragma once
#include <string>
#include <mutex>
#include <map>
#include <memory>
#include <thread>
#include <functional>
#include <condition_variable>
#include <queue>
#include <atomic>

namespace metrics {
    class MetricCollector;

    class AbstractMetric {
    public:
        AbstractMetric() = default;
        virtual ~AbstractMetric() = default;
        virtual std::string getName() = 0;
        virtual std::string getValueAsString() = 0;
    };

    template <typename T>
    class Metric: public AbstractMetric {
    public:
        //friend class MetricCollector;
        using MetricFunction = std::function <T()>;

        Metric() = default;
        Metric(std::string name, MetricFunction getMetricValue): name_(name), getMetricValue_(getMetricValue) {};
        Metric(std::string name): name_(name) {};

        std::string getName() override {
            return this->name_;
        };

        /*void setValue(T value) {
            mutexMetric.lock();
            value_ = value;
            mutexMetric.unlock();
        };*/

        std::string getValueAsString() override {
            return std::to_string(getMetricValue_());
        };

    private:
        std::string name_;
        MetricFunction getMetricValue_;
        std::mutex mutexMetric;
        T value_;
    };


   using MetricMessage = std::map<std::string, std::string>;

    class MetricStorage {
    public:
        void addMetric(AbstractMetric*);
        std::map <std::string, AbstractMetric*>& getStorage();
    private:
        std::map <std::string, AbstractMetric*> storage_;
        std::mutex mutexStorage;
    };


    class MetricCollector {
    public:
        MetricCollector(std::string filename, MetricStorage* metricStorage);
        void collect();
        ~MetricCollector();

    private:
        void writeToFile(MetricMessage);
        void workThreadFunc();
    
        std::thread workThread_;
        std::string filename_;
        MetricStorage* storagePtr_;
        std::mutex mutexCollect;
        std::mutex mutexQueue;
        std::condition_variable queueCV;
        std::queue <MetricMessage> metricsQueue;
        std::atomic_bool finished;
    };
   
    using metricPtr = AbstractMetric*;
    using storagePtr = MetricStorage*;
}
