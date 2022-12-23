#include "simulator.hpp"
#include "scheduler.hpp"
#include "printer.hpp"

time_unit millis = 1;
time_unit seconds = 1000;

Simulator::Simulator(std::vector<std::unique_ptr<Process>> &processes) : processes(std::move(processes)), numberOfProcesses(this->processes.size()), currentTime(0), simulationTime(0)
{
	this->sortProcessesByArrivalTime();
}

Simulator::~Simulator()
{
	processes.clear();
}

void Simulator::startSim(time_unit simulationTime, [[maybe_unused]] time_unit quantum)
{
	RR scheduler;
	std::vector<std::unique_ptr<Process>> results;
	logger = std::make_shared<Logger>("status.txt");
	this->simulationTime += simulationTime;
	for (; currentTime < simulationTime; currentTime++)
	{
		// std::cout << "Current Time: " << currentTime << " milliseconds\n"; // debugging only
		if (processes.size() > 0)
		{
			/*
			 * Since the processes are sorted by arrival time, we can check if the first process in the vector has arrived
			 * If it has, we add it to the ready queue and remove it from the vector
			 * Repeat this until the first process in the vector has not arrived yet
			 */
			while (processes.size() > 0 && processes[0]->getArrivalTime() == currentTime)
			{
				std::cout << "Process " << processes[0]->getPid() << " arrived at time " << currentTime << " milliseconds\n";
				logger->log(currentTime, processes[0]->getPid(), "Arrived");
				scheduler.addToReadyQueue(processes[0], currentTime);
				processes.erase(processes.begin());
			}
		}
		// else
		// {
		// 	std::cout << "No more processes to schedule\n";
		// }
		std::vector<std::unique_ptr<Process>> scheduled_processes = scheduler.schedule(currentTime, logger, quantum);
		results.insert(results.end(), std::make_move_iterator(scheduled_processes.begin()), std::make_move_iterator(scheduled_processes.end()));
	}
	// print results
	std::cout << "Simulation complete\n";
	std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << std::endl;
	for (auto &process : results)
	{
		std::cout << process->toString() << std::endl;
	}
	if (save_processes_to_file(results) == 0)
	{
		std::cout << "Processes saved to file successfully\n";
	}
	else
	{
		std::cout << "Error saving processes to file\n";
	}
}
