#include "simulator.hpp"
#include "scheduler.hpp"

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
	FCFS scheduler;
	this->simulationTime += simulationTime;
	for (; currentTime < simulationTime; currentTime++)
	{
		std::cout << "Current Time: " << currentTime << " milliseconds\n";
		if (processes.size() > 0)
		{
			if (processes[0]->arrivalTime == currentTime)
			{
				std::cout << "Process " << processes[0]->pid << " arrived at time " << currentTime << " milliseconds\n";
				scheduler.addToReadyQueue(processes[0]);
				processes.erase(processes.begin());
			}
		}
		else
		{
			std::cout << "No more processes to schedule\n";
			break;
		}
	}
}
