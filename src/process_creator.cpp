#include <cmath>
#include "process_creator.h"

Process **ProcessCreator::createProcesses(int numProcesses)
{
	srand(time(NULL));
	Process **processes = new Process *[numProcesses];
	for (int i = 0; i < numProcesses; i++)
	{
		processes[i] = new Process(createdProcesses, rand() % 10, rand() % 10);
		createdProcesses++;
	}
	return processes;
}
