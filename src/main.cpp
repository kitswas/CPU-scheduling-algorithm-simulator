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
#include "process_creator.h"
#include "scheduler.h"

int main()
{
	std::vector<std::unique_ptr<Process>> processes = ProcessCreator::createProcesses(5);
	std::cout << "Processes created" << std::endl;
	for (const auto &process : processes)
	{
		std::cout << *process << std::endl;
	}
	Scheduler scheduler(processes);
	scheduler.sortProcessesByArrivalTime();
	std::cout << "After sorting" << std::endl;
	for (const auto &process : scheduler.getProcesses())
	{
		std::cout << *process << std::endl;
	}
	return 0;
}
