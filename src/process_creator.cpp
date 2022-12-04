#include <cmath>
#include "process_creator.h"

std::vector<std::unique_ptr<Process>> ProcessCreator::createProcesses(int numProcesses)
{
	srand(static_cast<unsigned int>(time(NULL)));
	std::vector<std::unique_ptr<Process>> processes;
	for (int i = 0; i < numProcesses; i++)
	{
		processes.push_back(std::make_unique<Process>(Process(createdProcesses, rand() % 10, (rand() % 9) + 1))); // burstTime > 0
		createdProcesses++;
	}
	return processes;
}
