#include "scheduler.hpp"
#include "min_heap.hpp"

/**
 * @brief A First Come First Serve (FCFS) scheduler
 *
 */
void FCFS::schedule()
{
	MinHeap<std::unique_ptr<Process>> ready_queue(processes, compareArrivalTime);
	std::vector<std::unique_ptr<Process>> scheduled_processes;
	while (!ready_queue.isEmpty())
	{
		std::unique_ptr<Process> process = ready_queue.extractMin();
		if (process->arrivalTime > currentTime)
		{
			currentTime = process->arrivalTime;
		}
		process->startTime = currentTime;
		currentTime += process->burstTime;
		process->completionTime = currentTime;
		scheduled_processes.push_back(std::move(process));
	}
	processes = std::move(scheduled_processes);
	for (auto &process : processes)
	{
		process->turnAroundTime = process->completionTime - process->arrivalTime;
		process->waitingTime = process->turnAroundTime - process->burstTime;
		process->responseTime = process->startTime - process->arrivalTime;
	}
}
