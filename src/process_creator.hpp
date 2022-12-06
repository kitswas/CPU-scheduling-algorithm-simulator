#ifndef PROCESS_CREATOR_H
#define PROCESS_CREATOR_H

#include <memory>
#include <vector>
#include "process.hpp"

/**
 * @brief This class will create an array of processes and
 * assign a random arrival time and burst time to each process.
 *
 */
class ProcessCreator
{
private:
	inline static int createdProcesses = 0; // A monotonic counter to assign unique process ids

public:
	static std::vector<std::unique_ptr<Process>> createProcesses(int numProcesses);
};

#endif // PROCESS_CREATOR_H
