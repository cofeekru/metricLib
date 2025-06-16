/**
 * @file
 * @brief C++ Library for collecting and storing metrics
 * @version 1.0.0
 * @authors cofeekru
 */

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
    
    /**
    * @brief Abstract metric class with pure-vurtual function
    */
    class AbstractMetric {
    public:
        AbstractMetric() = default;
        virtual ~AbstractMetric() = default;
        virtual std::string getName() = 0;
        virtual std::string getValueAsString() = 0;
    };

    /**
    * @brief Template class for metric
    * @param[in] T Type of value that contains metric
    * 
    */
    template <typename T>
    class Metric: public AbstractMetric {
    public:
        /**
        * @brief Alias for function that returns value of metric
        */
        using MetricFunction = std::function <T()>;

        /**
        * @brief Default metric constructor
        */
        Metric() = default;

        /**
        * @brief Сonstructor that initializes the metric containing MetricFunction
        * @param[in] name Name of metric
        * @param[in] getMetricValue MetricFunction that returns a value of type T
        */
        Metric(std::string name, MetricFunction getMetricValue): name_(name), getMetricValue_(getMetricValue) {};

        /**
        * @brief Сonstructor that initializes the metric without MetricFunction
        * @param[in] name Name of metric
        */
        Metric(std::string name): name_(name) {};

        /**
        * @brief Method returning name of metric
        * @return Name of metric
        */
        std::string getName() override {
            return this->name_;
        };

        /**
        * @brief Method setting MetricFunction
        * @param[in] function MetricFunction
        */
        void setMetricFunction(MetricFunction function) {
            mutexMetric.lock();
            getMetricValue_ = function;
            mutexMetric.unlock();
        };

        /**
        * @brief Method getting value of metric
        * @return Value of metric converted to string
        */
        std::string getValueAsString() override {
            if (getMetricValue_ != nullptr) {
                return std::to_string(getMetricValue_());
            } else {
                return "";
            } 
        };

        /**
        * @brief Method getting value of metric
        * @return Value of metric
        */
        T getValue() {
            return getMetricValue_();
        };

    private:
        std::string name_;
        MetricFunction getMetricValue_ = nullptr;
        std::mutex mutexMetric;
    };

    /**
    * @brief Alias for pointer to metric for dynamic polymorphism
    */
    using MetricPtr = AbstractMetric*;


    /**
    * @brief Class MetricStorage that contains all metrics that added to its
    */
    class MetricStorage {
    public:
        /**
        * @brief Add metric to storage
        * @param[in] metricPointer Pointer to metric
        */
        void addMetric(MetricPtr metricPointer);

        /**
        * @brief Getting reference to storage
        * @param[in] metricPointer Pointer to metric
        */
        std::map <std::string, MetricPtr>& getStorage();

    private:
        std::map <std::string, MetricPtr> storage_;
        std::mutex mutexStorage;
    };
    /**
    * @brief Alias for pointer to MetricStorage
    */
    using StorageMetricPtr = MetricStorage*;


    /**
    * @brief Class MetricCollector that collect and storage all metrics
    */
    class MetricCollector {
    public:
        /**
        * @brief Сonstructor that initializes the MetricCollector
        * @param[in] filename File name that contain metrics
        * @param[in] metricStorage Pointer to object of MetricStorage
        */
        MetricCollector(std::string filename, StorageMetricPtr metricStorage);
        void collect();
        ~MetricCollector();

    private:
        using MetricMessage = std::map<std::string, std::string>;
        void writeToFile(MetricMessage);
        void workThreadFunc();
    
        std::thread workThread_;
        std::string filename_;
        StorageMetricPtr storagePtr_;
        std::mutex mutexCollect;
        std::mutex mutexQueue;
        std::condition_variable queueCV;
        std::queue <MetricMessage> metricsQueue;
        std::atomic_bool finished;
    };
   
    
}
