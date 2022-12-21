#ifndef PROCESS_CLASS
#define PROCESS_CLASS

#include <iostream>
#include <string>
#include <memory>

typedef long long time_unit;

class Process
{
private:
	const int pid; // The process id
	const time_unit arrivalTime;
	const time_unit burstTime;
	time_unit completionTime;
	time_unit turnAroundTime;
	time_unit waitingTime;
	time_unit responseTime;
	time_unit startTime;

public:
	Process(int pid, int arrivalTime, int burstTime);
	~Process();
	std::string toString() const;

	// Getters
	int getPid() const;
	time_unit getArrivalTime() const;
	time_unit getBurstTime() const;

	friend int compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);
};

int compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b);

std::ostream &operator<<(std::ostream &os, const Process &process);

#endif // PROCESS_CLASS
