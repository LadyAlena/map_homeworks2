#pragma once

#include <mutex>

class Data {
public:
    Data(const int value) noexcept : scalar_data(value) {}

    int get_scalar_data() const {
        return scalar_data;
    }

    void set_scalar_data(int newData) {
        scalar_data = newData;
    }

    std::mutex data_mutex;

private:
    int scalar_data;
};

namespace for_lock {
    void swap(Data& data1, Data& data2) {
        std::lock(data1.data_mutex, data2.data_mutex);
        std::lock_guard<std::mutex> lock1(data1.data_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(data2.data_mutex, std::adopt_lock);

        int temp = data1.get_scalar_data();
        data1.set_scalar_data(data2.get_scalar_data());
        data2.set_scalar_data(temp);
    }
}

namespace for_scoped_lock {
    void swap(Data& data1, Data& data2) {
        std::scoped_lock(data1.data_mutex, data2.data_mutex);

        int temp = data1.get_scalar_data();
        data1.set_scalar_data(data2.get_scalar_data());
        data2.set_scalar_data(temp);
    }
}

namespace for_unique_lock {
    void swap(Data& data1, Data& data2) {
        std::unique_lock<std::mutex> lock1(data1.data_mutex, std::defer_lock);
        std::unique_lock<std::mutex> lock2(data2.data_mutex, std::defer_lock);
        std::lock(lock1, lock2);

        int temp = data1.get_scalar_data();
        data1.set_scalar_data(data2.get_scalar_data());
        data2.set_scalar_data(temp);
    }
}