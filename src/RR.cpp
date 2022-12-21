#include "scheduler.hpp"
#include "process.hpp"
#include <memory>
#include <vector>

std::ostream &operator<<(std::ostream &os, const RRProcess &rrprocess)
{
	return os << "Process: " << rrprocess.process->getPid() << ", Remaining Burst Time: " << rrprocess.remainingBurstTime << ", Start Time: " << rrprocess.startTime;
}

int compareStartTime(const std::unique_ptr<RRProcess> &a, const std::unique_ptr<RRProcess> &b)
{
	if (a->startTime < b->startTime)
	{
		return -1;
	}
	else if (a->startTime > b->startTime)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief A Round Robin (RR) scheduler
 *
 */
RR::RR() : ready_queue(compareStartTime)
{
}

RR::~RR() {}

bool RR::addToReadyQueue(std::unique_ptr<Process> &process, time_unit currentTime)
{
	ready_queue.insert(std::make_unique<RRProcess>(std::move(process), process->getBurstTime(), currentTime));
	// std::cout << "RR::addToReadyQueue() called\n"; // debugging only
	return true;
}

// TODO: implement this
std::vector<std::unique_ptr<Process>> RR::schedule(time_unit &currentTime, std::shared_ptr<Logger> logger)
{
	std::vector<std::unique_ptr<Process>> scheduled_processes;
	static time_unit currentProcessRemainingTime = 0;
	static std::unique_ptr<RRProcess> currentProcess = nullptr;

	--currentProcessRemainingTime;

	if (currentProcessRemainingTime == 0) // won't enter on first run, as currentProcessRemainingTime will be -1
	{
		// process completed
		currentProcess->process->setCompletionTime(currentTime);
		// log completion
		std::cout << "Process " << currentProcess->process->getPid() << " ended at time " << currentTime << " milliseconds\n";
		logger->log(currentTime, currentProcess->process->getPid(), "Exit");
		// calculate metrics
		currentProcess->process->setTurnAroundTime(currentProcess->process->getCompletionTime() - currentProcess->process->getArrivalTime());
		currentProcess->process->setWaitingTime(currentProcess->process->getTurnAroundTime() - currentProcess->process->getBurstTime());
		currentProcess->process->setResponseTime(currentProcess->process->getStartTime() - currentProcess->process->getArrivalTime());
		// add to scheduled processes
		scheduled_processes.push_back(std::move(currentProcess->process));
		currentProcess = nullptr;
	}

	if (currentProcess == nullptr)
	{
		// check if there are any more processes in the ready queue
		if (!ready_queue.isEmpty())
		{
			currentProcess = ready_queue.extractMin();
			currentProcess->process->setStartTime(currentTime);
			currentProcessRemainingTime = currentProcess->process->getBurstTime();
			// log start
			std::cout << "Process " << currentProcess->process->getPid() << " started at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->process->getPid(), "Running");
		}
	}

	return scheduled_processes;
}
