#include "include/metricsLib.hpp"
#include <iostream>

double get_cpu_usage() {
    // Симуляция загрузки ЦП
    double seed = double(rand() % 200000);
    double cpu_usage = seed / 100000;
    return cpu_usage;
}

int get_http_requests_rps() {
    // Симуляция количества HTTP запросов в секунду
    return rand() % 50 + 10;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Отсутвует путь к файлу" << '\n';
        return 1;
    }
    srand(time(nullptr));
    
    metrics::Metric<int>httpRequests{"HTTP", get_http_requests_rps};
    metrics::Metric<float>cpuUsage{"CPU", get_cpu_usage};

    metrics::MetricPtr httpRequestsPtr = &httpRequests;
    metrics::MetricPtr cpuUsagePtr = &cpuUsage;
    
    metrics::MetricStorage storageMetrics;
    storageMetrics.addMetric(httpRequestsPtr);
    storageMetrics.addMetric(cpuUsagePtr);
    

    metrics::StorageMetricPtr storageMetricPtr = &storageMetrics;
    
    std::string filename = argv[1];
    metrics::MetricCollector collector{filename, storageMetricPtr};
    
    
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        collector.collect(); 
    }
    
    return 0;
}
