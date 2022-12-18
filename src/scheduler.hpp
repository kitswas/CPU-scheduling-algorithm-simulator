#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "process.hpp"
#include "min_heap.hpp"

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:

public:
	virtual void schedule() = 0;
	virtual bool addToReadyQueue(std::unique_ptr<Process> &process) = 0;
	// virtual void printSchedule() = 0;
};

class FCFS : public Scheduler
{
private:
	MinHeap<std::unique_ptr<Process>> ready_queue;
public:
	FCFS();
	~FCFS();
	void schedule();
	bool addToReadyQueue(std::unique_ptr<Process> &process);
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
