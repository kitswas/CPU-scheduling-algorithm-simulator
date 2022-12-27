/**
 * @file main.cpp
 * @brief
 * @author Swastik Pal
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 * Comments _can_ be written in [**Markdown**](https://www.markdownguide.org/cheat-sheet/).
 */

#include "process_creator.hpp"
#include "simulator.hpp"

int main()
{
	std::vector<std::unique_ptr<Process>> processes = ProcessCreator::createProcesses(5);
	std::cout << "Processes created" << std::endl;
	std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << std::endl;
	for (const auto &process : processes)
	{
		std::cout << *process << std::endl;
	}
	Simulator sim(processes);
	sim.sortProcessesByArrivalTime();
	std::cout << "Processes sorted" << std::endl;
	// std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << std::endl;
	for (const auto &process : sim.getProcesses())
	{
		std::cout << *process << std::endl;
	}

	// sim.startSim(std::make_unique<RR>(), 100, 2); // debugging only

	// Ask the user for the scheduler type
	int scheduler_type;
	std::cout << "Choose a scheduler type:\n1. FCFS\n2. RR\n3. CFS\n";
	std::cin >> scheduler_type;
	std::unique_ptr<Scheduler> scheduler; // must be a pointer to prevent slicing
	switch (scheduler_type)
	{
	case 1:
		scheduler = std::make_unique<FCFS>();
		break;
	case 2:
		scheduler = std::make_unique<RR>();
		break;
	case 3:
		scheduler = std::make_unique<CFS>();
		break;
	default:
		std::cout << "Invalid choice. Exiting...\n";
		return 0;
	}
	// Ask the user for the simulation time
	time_unit simulationTime;
	std::cout << "Enter the simulation time in milliseconds: ";
	std::cin >> simulationTime;
	// Ask the user for the time quantum, if required
	time_unit quantum;
	switch (scheduler_type)
	{
	case 2:
	case 3:
		std::cout << "Enter the time slice (quantum) in milliseconds: ";
		std::cin >> quantum;
	}

	sim.startSim(std::move(scheduler), simulationTime, quantum);

	return 0;
}
