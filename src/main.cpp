#include "Simulation.hpp"
#include <chrono>
#include <thread>

int main()
{
	Simulation world;
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	return 0;
}
