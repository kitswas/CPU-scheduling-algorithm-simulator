#include <iostream>

class Process
{
private:
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
};

Process::Process(int pid, int arrivalTime, int burstTime) : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime)
{
	completionTime = -1;
	turnAroundTime = -1;
	waitingTime = -1;
	responseTime = -1;
}

Process::~Process()
{
}

std::string Process::toString() const
{
	return std::to_string(pid) + "\t" +
		   std::to_string(arrivalTime) + "\t" +
		   std::to_string(burstTime) + "\t" +
		   std::to_string(completionTime) + "\t" +
		   std::to_string(turnAroundTime) + "\t" +
		   std::to_string(waitingTime) + "\t" +
		   std::to_string(responseTime);
}

std::ostream &operator<<(std::ostream &os, const Process &process)
{
	return os << process.toString();
}
