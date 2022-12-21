#include "scheduler.hpp"
#include "process.hpp"
#include <memory>
#include <vector>

/**
 * @brief A First Come First Serve (FCFS) scheduler
 *
 */
void FCFS::schedule()
{
	// std::vector<std::unique_ptr<Process>> scheduled_processes;
	// while (!ready_queue.isEmpty())
	// {
	// 	std::unique_ptr<Process> process = ready_queue.extractMin();
	// 	if (process->arrivalTime > currentTime)
	// 	{
	// 		currentTime = process->arrivalTime;
	// 	}
	// 	process->startTime = currentTime;
	// 	currentTime += process->burstTime;
	// 	process->completionTime = currentTime;
	// 	scheduled_processes.push_back(std::move(process));
	// }
	// processes = std::move(scheduled_processes);
	// for (auto &process : processes)
	// {
	// 	process->turnAroundTime = process->completionTime - process->arrivalTime;
	// 	process->waitingTime = process->turnAroundTime - process->burstTime;
	// 	process->responseTime = process->startTime - process->arrivalTime;
	// }
}

FCFS::FCFS() : ready_queue(compareArrivalTime)
{
}

FCFS::~FCFS() {}

bool FCFS::addToReadyQueue(std::unique_ptr<Process> &process)
{
	ready_queue.insert(std::move(process));
	// std::cout << "FCFS::addToReadyQueue() called\n"; // debugging only
	return true;
}
