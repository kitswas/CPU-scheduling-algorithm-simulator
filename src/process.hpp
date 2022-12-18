#ifndef PROCESS_CLASS
#define PROCESS_CLASS

#include <iostream>
#include <string>
#include <memory>

typedef long long time_unit;

class Process
{
public:
	const int pid; // The process id
	const time_unit arrivalTime;
	const time_unit burstTime;
	time_unit completionTime;
	time_unit turnAroundTime;
	time_unit waitingTime;
	time_unit responseTime;
	time_unit startTime;

	Process(int pid, int arrivalTime, int burstTime);
	~Process();
	std::string toString() const;

	friend time_unit compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);
};

time_unit compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);

std::ostream &operator<<(std::ostream &os, const Process &process);

#endif // PROCESS_CLASS
