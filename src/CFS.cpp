#include "scheduler.hpp"

std::ostream &operator<<(std::ostream &os, const CFSProcess &cfsprocess)
{
	return os << "Process: " << cfsprocess.process->getPid() << ", VRuntime: " << cfsprocess.vruntime;
}

/**
 * @brief Compare two CFSProcess objects by their vruntime.
 *
 */
int compareVRuntime(const std::unique_ptr<CFSProcess> &a, const std::unique_ptr<CFSProcess> &b)
{
	if (a->vruntime < b->vruntime)
	{
		return -1;
	}
	else if (a->vruntime > b->vruntime)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief A Completely Fair Scheduler (CFS)
 *
 */
CFS::CFS() : ready_queue(compareVRuntime)
{
}

CFS::~CFS()
{
}

std::vector<std::unique_ptr<Process>> CFS::schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum)
{
	std::vector<std::unique_ptr<Process>> scheduled_processes;
	static std::unique_ptr<CFSProcess> currentProcess = nullptr;
	size_t numProcesses = ready_queue.size() + (currentProcess != nullptr ? 1 : 0);
	if (numProcesses > 1) // prevent division by zero
	{
		quantum = quantum / numProcesses;
	}
	if (quantum == 0)
	{
		quantum = 1; // minimum quantum
	}

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
		else if (currentTime >= (currentProcess->reentryTime + quantum))
		{
			// log preempted
			std::cout << "Process " << currentProcess->process->getPid() << " preempted at time " << currentTime << " milliseconds\n";
			logger->log(currentTime, currentProcess->process->getPid(), "Preempted");
			// update vruntime
			currentProcess->vruntime += currentProcess->process->getBurstTime() - currentProcess->remainingBurstTime;
			// reinsert into ready queue
			currentProcess->reentryTime = currentTime;
			ready_queue.insert(std::move(currentProcess));
			currentProcess = nullptr;
		}
	}

	if (currentProcess == nullptr)
	{
		// check if there are any more processes in the ready queue
		if (ready_queue.size() > 0)
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

bool CFS::addToReadyQueue(std::unique_ptr<Process> &process, [[maybe_unused]] time_unit _currentTime)
{
	ready_queue.insert(std::make_unique<CFSProcess>(std::move(process), 0));
	return false;
}
