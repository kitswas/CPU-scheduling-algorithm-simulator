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

#include <iostream>
#include "process_creator.hpp"
#include "scheduler.hpp"
#include "min_heap.hpp"
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
	// FCFS scheduler(processes);
	// scheduler.schedule();
	std::cout << "Processes sorted" << std::endl;
	// std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << std::endl;
	for (const auto &process : sim.getProcesses())
	{
		std::cout << *process << std::endl;
	}
	sim.startSim(100);
	return 0;
}
