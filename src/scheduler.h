#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "process.h"

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:
	Process **processes;
	int numberOfProcesses;
	int currentTime;

public:
	virtual void schedule() = 0;
	virtual void printSchedule() = 0;
};

#endif // SCHEDULER_CLASS
