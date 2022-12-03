#ifndef PROCESS_CREATOR_H
#define PROCESS_CREATOR_H

#include "process.h"

/**
 * @brief This class will create an array of processes and
 * assign a random arrival time and burst time to each process.
 *
 */
class ProcessCreator
{
private:
	inline static int createdProcesses = 0;

public:
	static Process **createProcesses(int numProcesses);
};

#endif // PROCESS_CREATOR_H
