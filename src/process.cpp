#include <iostream>
#include "process.hpp"

Process::Process(int pid, int arrivalTime, int burstTime) : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime)
{
	this->completionTime = -1;
	this->turnAroundTime = -1;
	this->waitingTime = -1;
	this->responseTime = -1;
	this->startTime = -1;
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

int compareArrivalTime(const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
{
	if (a->arrivalTime < b->arrivalTime)
	{
		return -1;
	}
	else if (a->arrivalTime > b->arrivalTime)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Process::getPid() const
{
	return pid;
}

time_unit Process::getArrivalTime() const
{
	return arrivalTime;
}

time_unit Process::getBurstTime() const
{
	return burstTime;
}

time_unit Process::getCompletionTime() const
{
	return completionTime;
}

time_unit Process::getTurnAroundTime() const
{
	return turnAroundTime;
}

time_unit Process::getWaitingTime() const
{
	return waitingTime;
}

time_unit Process::getResponseTime() const
{
	return responseTime;
}

time_unit Process::getStartTime() const
{
	return startTime;
}

void Process::setCompletionTime(time_unit completionTime)
{
	this->completionTime = completionTime;
}

void Process::setTurnAroundTime(time_unit turnAroundTime)
{
	this->turnAroundTime = turnAroundTime;
}

void Process::setWaitingTime(time_unit waitingTime)
{
	this->waitingTime = waitingTime;
}

void Process::setResponseTime(time_unit responseTime)
{
	this->responseTime = responseTime;
}

void Process::setStartTime(time_unit startTime)
{
	this->startTime = startTime;
}
