#ifndef PROCESS_CLASS
#define PROCESS_CLASS

#include <iostream>
#include <string>
#include "min_heap.h"

class Process
{
protected:
	int pid;
	int arrivalTime;
	int burstTime;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
	int responseTime;

public:
	Process(int pid, int arrivalTime, int burstTime);
	~Process();
	std::string toString() const;
	friend class Scheduler;
	friend class MinHeap<std::unique_ptr<Process>>;
};

std::ostream &operator<<(std::ostream &os, const Process &process);

#endif // PROCESS_CLASS
