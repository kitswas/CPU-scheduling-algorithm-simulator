#include <iostream>
#include "process.hpp"

Process::Process(int pid, int arrivalTime, int burstTime) : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime)
{
	this->completionTime = -1;
	this->turnAroundTime = -1;
	this->waitingTime = -1;
	this->responseTime = -1;
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

time_unit compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
{
	return a->arrivalTime - b->arrivalTime;
}
