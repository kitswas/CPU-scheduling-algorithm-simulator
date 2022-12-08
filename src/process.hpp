#ifndef PROCESS_CLASS
#define PROCESS_CLASS

#include <iostream>
#include <string>
#include <memory>

class Process
{
public:
	const int pid; // The process id
	const int arrivalTime;
	const int burstTime;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
	int responseTime;
	int startTime;

	Process(int pid, int arrivalTime, int burstTime);
	~Process();
	std::string toString() const;

	friend int compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);
};

int compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);

std::ostream &operator<<(std::ostream &os, const Process &process);

#endif // PROCESS_CLASS
