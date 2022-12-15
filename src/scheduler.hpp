#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:

public:
	virtual void schedule() = 0;
	// virtual void printSchedule() = 0;
};

class FCFS : public Scheduler
{
private:
	/* data */
public:
	void schedule();
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
