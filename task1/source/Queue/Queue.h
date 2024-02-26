#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

struct Queue {

	Queue(const size_t max_counter);

	void add_client();
	void process_client();

private:
	std::mutex m;
	size_t counter{};
	size_t max_counter{};
};