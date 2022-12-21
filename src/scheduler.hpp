#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "process.hpp"
#include "min_heap.hpp"
#include "logger.hpp"

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:
public:
	virtual std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger) = 0;
	virtual bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit currentTime) = 0;
	// virtual void printSchedule() = 0;
};

class FCFS : public Scheduler
{
private:
	MinHeap<std::unique_ptr<Process>> ready_queue;

public:
	FCFS();
	~FCFS();
	std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger);
	bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit _currentTime=-1);
};

struct RRProcess
{
	std::unique_ptr<Process> process;
	time_unit remainingBurstTime;
	time_unit startTime;
};

std::ostream &operator<<(std::ostream &os, const RRProcess &rrprocess);

class RR : public Scheduler
{
private:
	MinHeap<std::unique_ptr<RRProcess>> ready_queue;

public:
	RR();
	~RR();
	std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger);
	bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit currentTime);
};

class CFS : public Scheduler
{
private:
	/* data */
};

#endif // SCHEDULER_CLASS
