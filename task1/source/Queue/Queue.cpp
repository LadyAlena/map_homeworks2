#include "Queue.h"

Queue::Queue(const size_t max_counter) : max_counter(max_counter) {}

void Queue::add_client() {
	std::lock_guard lg(m);
	do {
		counter++;
		std::cout << "in thread " << std::this_thread::get_id() << " client is added. Number of clients = " << counter << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	} while (counter < max_counter);
}

void Queue::process_client() {
	std::lock_guard lg(m);
	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		counter--;
		std::cout << "in thread " << std::this_thread::get_id() << " client is processed. Number of clients = " << counter << std::endl;
	} while (counter);
}