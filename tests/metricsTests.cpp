#include <gtest/gtest.h>
#include "../include/metricsLib.hpp"


TEST(MetricTests, getNameTest) {
    metrics::Metric<int> m{"testMetric"};

    std::string expected = "testMetric";
    std::string received = m.getName();

    ASSERT_EQ(expected, received);
};

TEST(MetricTests, getValueTest) {
    srand(time(nullptr));
    int value = rand() % 10000;
    std::function <int()> func{[&]{return value;}};
    metrics::Metric<int> m{"testMetric", func};

    std::string expected = std::to_string(value);
    std::string received = m.getValueAsString();
    ASSERT_EQ(expected, received);
};

TEST(MetricTests, setMetricFunctionTest) {
    srand(time(nullptr));
    int value = rand() % 10000;

    metrics::Metric<int> m{"testMetric"};
    
    std::function <int()> func([&]{return value;});

    m.setMetricFunction(func);
    int expected = value;
    int received = m.getValue();

    ASSERT_EQ(expected, received);
};

TEST(MetricStorageTest, addMetricTest) {
    metrics::MetricStorage ms;
    std::string nameMetric = "test_1";
    metrics::Metric<int> m{nameMetric};
    ms.addMetric(&m);
    
    std::map <std::string, metrics::MetricPtr> storage = ms.getStorage();

    ASSERT_TRUE(storage.contains(nameMetric));
    
};

TEST(MetricStorageTest, stressStorageTest) {
    metrics::MetricStorage ms;
    for (size_t i = 0; i < 100000; i++) {
        std::string nameMetric = "test_" + std::to_string(i);
        metrics::Metric<int> m{nameMetric};
        ms.addMetric(&m);
    }
    std::map <std::string, metrics::MetricPtr> storage = ms.getStorage();

    for (size_t i = 0; i < 100000; i++) {
        std::string nameMetric = "test_" + std::to_string(i);
        ASSERT_TRUE(storage.contains(nameMetric));
    }
    
};