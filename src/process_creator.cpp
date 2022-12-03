#include <cmath>
#include "process_creator.h"

std::vector<std::unique_ptr<Process>> ProcessCreator::createProcesses(int numProcesses)
{
	srand(time(NULL));
	std::vector<std::unique_ptr<Process>> processes;
	for (int i = 0; i < numProcesses; i++)
	{
		processes.push_back(std::make_unique<Process>(Process(createdProcesses, rand() % 10, rand() % 10)));
		createdProcesses++;
	}
	return processes;
}
