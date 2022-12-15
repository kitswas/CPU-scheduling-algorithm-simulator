#ifndef SIMULATOR_CLASS
#define SIMULATOR_CLASS

#include "process.hpp"
#include <memory>
#include <vector>
#include <algorithm>

typedef unsigned long time_unit;

class Simulator
{
private:
	std::vector<std::unique_ptr<Process>> processes;
	std::size_t numberOfProcesses;
	time_unit currentTime;
	time_unit simulationTime;

public:
	Simulator(std::vector<std::unique_ptr<Process>> &processes);
	~Simulator();
	void sortProcessesByArrivalTime();
	const std::vector<std::unique_ptr<Process>> &getProcesses() const;
	void startSim(time_unit simulationTime);
};

inline const std::vector<std::unique_ptr<Process>> &Simulator::getProcesses() const
{
	return processes;
}

inline void Simulator::sortProcessesByArrivalTime()
{
	std::sort(processes.begin(), processes.end(), [](const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
			  { return a->arrivalTime < b->arrivalTime; });
}

#endif // SIMULATOR_CLASS
