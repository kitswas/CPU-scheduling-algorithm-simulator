#include "scheduler.hpp"
#include "process.hpp"
#include <memory>
#include <vector>

std::ostream &operator<<(std::ostream &os, const RRProcess &rrprocess)
{
	return os << "Process: " << rrprocess.process->getPid() << ", Remaining Burst Time: " << rrprocess.remainingBurstTime << ", Start Time: " << rrprocess.reentryTime;
}

int compareReentryTime(const std::unique_ptr<RRProcess> &a, const std::unique_ptr<RRProcess> &b)
{
	if (a->reentryTime < b->reentryTime)
	{
		return -1;
	}
	else if (a->reentryTime > b->reentryTime)
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
RR::RR() : ready_queue(compareReentryTime)
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
std::vector<std::unique_ptr<Process>> RR::schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum)
{
	std::vector<std::unique_ptr<Process>> scheduled_processes;
	static std::unique_ptr<RRProcess> currentProcess = nullptr;

	if (currentProcess != nullptr)
	{
		if (currentProcess->remainingBurstTime > 0 && currentTime < (currentProcess->reentryTime + quantum))
		{
			currentProcess->remainingBurstTime--;
		}
		if (currentProcess->remainingBurstTime == 0)
		{
			// process completed
			currentProcess->process->setCompletionTime(currentTime);
			// log end
			std::cout << "Process " << currentProcess->process->getPid() << " ended at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->process->getPid(), "Finished");
			// calculate metrics
			currentProcess->process->setTurnAroundTime(currentProcess->process->getCompletionTime() - currentProcess->process->getArrivalTime());
			currentProcess->process->setWaitingTime(currentProcess->process->getTurnAroundTime() - currentProcess->process->getBurstTime());
			currentProcess->process->setResponseTime(currentProcess->process->getStartTime() - currentProcess->process->getArrivalTime());
			// add to scheduled_processes
			scheduled_processes.push_back(std::move(currentProcess->process));
			currentProcess = nullptr;
		}
		else if (currentTime == (currentProcess->reentryTime + quantum))
		{
			// log preempted
			std::cout << "Process " << currentProcess->process->getPid() << " preempted at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->process->getPid(), "Preempted");
			// reinsert into ready queue
			currentProcess->reentryTime = currentTime + 1; // +1 to reinsert after new arrivals at the same time
			ready_queue.insert(std::move(currentProcess));
			currentProcess = nullptr;
		}
	}

	if (currentProcess == nullptr)
	{
		// check if there are any more processes in the ready queue
		if (!ready_queue.isEmpty())
		{
			currentProcess = ready_queue.extractMin();
			if (currentProcess->process->getStartTime() == -1) // on first run
			{
				currentProcess->process->setStartTime(currentTime);
				currentProcess->remainingBurstTime = currentProcess->process->getBurstTime();
			}
			currentProcess->reentryTime = currentTime;
			// log start
			std::cout << "Process " << currentProcess->process->getPid() << " started at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->process->getPid(), "Running");
		}
		else
		{
			return scheduled_processes; // no more processes to schedule
		}
	}

	return scheduled_processes;
}
