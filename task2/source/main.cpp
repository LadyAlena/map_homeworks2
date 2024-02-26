#include <iostream>
#include <iomanip>

#include <random>

#include <vector>

#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#include <Windows.h>

#include "../source/console_parameters/console.h"

std::mutex console_mutex;
std::atomic_flag existence_input_table_headers = ATOMIC_FLAG_INIT;

void draw(const std::size_t& thread_number, const std::size_t& total_threads, const std::size_t& calculation_length) {

    auto filledChar = "█";
    auto emptyChar = "▒";

    static std::vector<bool> flags_error(total_threads, false);

    std::chrono::steady_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    /* Set headers */
    {
        std::lock_guard<std::mutex> lock(console_mutex);

        if (!existence_input_table_headers.test_and_set()) {
            
            std::cout << "#" << std::setw(5) << "id" << std::setw(17) << "Progress bar" << std::setw(calculation_length - 6) << "Time" << std::endl;
            
            for (size_t i = 1; i <= total_threads; ++i) {
                std::cout << i << std::endl;
            }

            for (size_t i = 1; i <= total_threads; ++i) {
                
                console::parameters::set_position(11, i);

                for (int i = 0; i < calculation_length; ++i) {
                    std::cout << emptyChar;
                }

                std::cout << std::endl;
            }

        }
    }

    /* Get thread id */
    {
        std::lock_guard<std::mutex> lock(console_mutex);

        auto id_thread = std::this_thread::get_id();

        console::parameters::set_position(4, thread_number + 1);

        std::cout << id_thread;
    }

    /* Loading the progress bar */
    for (int i = 0; i < calculation_length && !flags_error[thread_number]; ++i) {

        std::lock_guard<std::mutex> lock(console_mutex);

        console::parameters::set_position(11 + i, thread_number + 1);

        srand(time(NULL));

        // Simulate error with a random probability
        if (rand() % 100 == 0) {
            flags_error[thread_number] = true;
        }

        if (!flags_error[thread_number]) {
            std::cout << filledChar;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

    /* Get loading time of the progress bar */
    {
        std::lock_guard<std::mutex> lock(console_mutex);

        console::parameters::set_position(calculation_length + 13, thread_number + 1);

        if (!flags_error[thread_number]) {
            std::cout << std::fixed << std::setprecision(3) << duration << " s";
        }
        else {
            console::parameters::set_color(FOREGROUND_RED, 0);
            std::cout << "error";
        }

        console::parameters::set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
    }
}

int main(int argc, char** argv) {

    std::size_t N = 25;
	std::size_t calculation_length = 20;

    std::vector<std::thread> threads;

    for (size_t i = 0; i < N; ++i) {
        threads.emplace_back(draw, i, N, calculation_length);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    console::parameters::set_position(0, N + 1);

	return 0;
}