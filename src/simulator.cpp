#include "simulator.hpp"

time_unit millis = 1;
time_unit seconds = 1000;

Simulator::Simulator(std::vector<std::unique_ptr<Process>> &processes) : processes(std::move(processes)), numberOfProcesses(this->processes.size()), currentTime(0), simulationTime(0)
{
	this->sortProcessesByArrivalTime();
}

Simulator::~Simulator()
{
	processes.clear();
	processes.~vector();
}

void Simulator::startSim(time_unit simulationTime)
{
	this->simulationTime += simulationTime;
	for (; currentTime < simulationTime; currentTime++)
	{
		std::cout << "Current Time: " << currentTime << " milliseconds\n";
	}
}
