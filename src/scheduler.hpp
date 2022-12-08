#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "process.hpp"
#include <memory>
#include <vector>
#include <algorithm>

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:
	std::vector<std::unique_ptr<Process>> processes;
	std::size_t numberOfProcesses;
	int currentTime;

public:
	virtual void schedule() = 0;
	// virtual void printSchedule() = 0;
	void sortProcessesByArrivalTime();
	const std::vector<std::unique_ptr<Process>> &getProcesses() const;
	Scheduler(std::vector<std::unique_ptr<Process>> &processes) : processes(std::move(processes)), numberOfProcesses(this->processes.size()), currentTime(0){};
};

inline const std::vector<std::unique_ptr<Process>> &Scheduler::getProcesses() const
{
	return processes;
}

inline void Scheduler::sortProcessesByArrivalTime()
{
	std::sort(processes.begin(), processes.end(), [](const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
			  { return a->arrivalTime < b->arrivalTime; });
}

class FCFS : public Scheduler
{
private:
	/* data */
public:
	void schedule();
	FCFS(std::vector<std::unique_ptr<Process>> &processes) : Scheduler(processes){};
};

class RR : public Scheduler
{
private:
	/* data */
};

class CFS : public Scheduler
{
private:
	/* data */
};

#endif // SCHEDULER_CLASS
