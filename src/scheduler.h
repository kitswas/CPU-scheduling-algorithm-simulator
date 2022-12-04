#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "process.h"
#include <memory>
#include <vector>

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:
	std::vector<std::unique_ptr<Process>> processes;
	int numberOfProcesses;
	int currentTime;

public:
	virtual void schedule() = 0;
	virtual void printSchedule() = 0;
};

class FCFS : public Scheduler
{
private:
	/* data */
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
