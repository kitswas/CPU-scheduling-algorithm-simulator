#ifndef SIMULATOR_CLASS
#define SIMULATOR_CLASS

#include "scheduler.hpp"
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
	static void sortProcessesByPid(std::vector<std::unique_ptr<Process>> &processes);
	const std::vector<std::unique_ptr<Process>> &getProcesses() const;
	void startSim(std::unique_ptr<Scheduler> scheduler, time_unit simulationTime, time_unit quantum);
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

inline void Simulator::sortProcessesByPid(std::vector<std::unique_ptr<Process>> &processes)
{
	std::sort(processes.begin(), processes.end(), [](const std::unique_ptr<Process> &a, const std::unique_ptr<Process> &b)
			  { return a->getPid() < b->getPid(); });
}

#endif // SIMULATOR_CLASS
