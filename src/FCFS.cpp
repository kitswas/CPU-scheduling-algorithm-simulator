#include "scheduler.hpp"
#include "process.hpp"
#include <memory>
#include <vector>

/**
 * @brief A First Come First Serve (FCFS) scheduler
 *
 */
FCFS::FCFS() : ready_queue(compareArrivalTime)
{
}

FCFS::~FCFS() {}

bool FCFS::addToReadyQueue(std::unique_ptr<Process> &process, [[maybe_unused]] time_unit _currentTime)
{
	ready_queue.insert(std::move(process));
	// std::cout << "FCFS::addToReadyQueue() called\n"; // debugging only
	return true;
}

std::vector<std::unique_ptr<Process>> FCFS::schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, [[maybe_unused]] time_unit quantum)
{
	std::vector<std::unique_ptr<Process>> scheduled_processes;
	static time_unit currentProcessRemainingTime = 0;
	static std::unique_ptr<Process> currentProcess = nullptr;

	--currentProcessRemainingTime;

	if (currentProcessRemainingTime == 0) // won't enter on first run, as currentProcessRemainingTime will be -1
	{
		// process completed
		currentProcess->setCompletionTime(currentTime);
		// log completion
		std::cout << "Process " << currentProcess->getPid() << " ended at time " << currentTime << " milliseconds\n";
		logger->log(currentTime, currentProcess->getPid(), "Exit");
		// calculate metrics
		currentProcess->setTurnAroundTime(currentProcess->getCompletionTime() - currentProcess->getArrivalTime());
		currentProcess->setWaitingTime(currentProcess->getTurnAroundTime() - currentProcess->getBurstTime());
		currentProcess->setResponseTime(currentProcess->getStartTime() - currentProcess->getArrivalTime());
		// add to scheduled processes
		scheduled_processes.push_back(std::move(currentProcess));
		currentProcess = nullptr;
	}

	if (currentProcess == nullptr)
	{
		// check if there are any more processes in the ready queue
		if (!ready_queue.isEmpty())
		{
			currentProcess = ready_queue.extractMin();
			currentProcess->setStartTime(currentTime);
			currentProcessRemainingTime = currentProcess->getBurstTime();
			// log start
			std::cout << "Process " << currentProcess->getPid() << " started at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->getPid(), "Running");
		}
	}

	return scheduled_processes;
}
