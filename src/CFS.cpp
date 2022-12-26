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

std::vector<std::unique_ptr<Process>> CFS::schedule([[maybe_unused]] time_unit &currentTime, [[maybe_unused]] std::shared_ptr<Logger> logger, [[maybe_unused]] time_unit quantum)
{
	return std::vector<std::unique_ptr<Process>>();
}

bool CFS::addToReadyQueue(std::unique_ptr<Process> &process, [[maybe_unused]] time_unit _currentTime)
{
	ready_queue.insert(std::make_unique<CFSProcess>(std::move(process), 0));
	return false;
}
