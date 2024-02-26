#include <iostream>
#include <mutex>

#include "../source/data_operations.hpp"

enum {
    TYPE_LOCK,
    FOR_LOCK,
    FOR_SCOPED_LOCK,
    FOR_UNIQUE_LOCK
};

int main() {
    Data data1(10);
    Data data2(20);

    std::cout << "Before swap: data1.scalar_data = " << data1.get_scalar_data() << ", data2.scalar_data = " << data2.get_scalar_data() << std::endl;

    auto lock_type = FOR_UNIQUE_LOCK;

    switch (lock_type) {
    case TYPE_LOCK:
        std::cout << "lock type are not selected" << std::endl;
        break;
    case FOR_LOCK:
        std::cout << "The lock is selected: std::lock" << std::endl;
        for_lock::swap(data1, data2);
        break;
    case FOR_SCOPED_LOCK:
        std::cout << "The lock is selected: std::scoped_lock" << std::endl;
        for_scoped_lock::swap(data1, data2);
        break;
    case FOR_UNIQUE_LOCK:
        std::cout << "The lock is selected: std::unique_lock" << std::endl;
        for_unique_lock::swap(data1, data2);
        break;
    default:
        break;
    }

    std::cout << "After swap: data1.scalar_data = " << data1.get_scalar_data() << ", data2.scalar_data = " << data2.get_scalar_data() << std::endl;

    return 0;
}