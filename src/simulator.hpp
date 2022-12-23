#ifndef SIMULATOR_CLASS
#define SIMULATOR_CLASS

#include "process.hpp"
#include "logger.hpp"
#include <memory>
#include <vector>
#include <algorithm>

class Simulator
{
private:
	std::vector<std::unique_ptr<Process>> processes;
	std::size_t numberOfProcesses;
	std::shared_ptr<Logger> logger;
	time_unit currentTime;
	time_unit simulationTime;

public:
	Simulator(std::vector<std::unique_ptr<Process>> &processes);
	~Simulator();
	void sortProcessesByArrivalTime();
	const std::vector<std::unique_ptr<Process>> &getProcesses() const;
	void startSim(time_unit simulationTime, time_unit quantum);
};

inline const std::vector<std::unique_ptr<Process>> &Simulator::getProcesses() const
{
	return processes;
}

inline void Simulator::sortProcessesByArrivalTime()
{
	std::sort(processes.begin(), processes.end(), [](const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
			  { return a->getArrivalTime() < b->getArrivalTime(); });
}

#endif // SIMULATOR_CLASS
