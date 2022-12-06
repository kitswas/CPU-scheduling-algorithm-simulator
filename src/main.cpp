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

int main()
{
	std::vector<std::unique_ptr<Process>> processes = ProcessCreator::createProcesses(5);
	std::cout << "Processes created" << std::endl;
	for (const auto &process : processes)
	{
		std::cout << *process << std::endl;
	}
	// FCFS scheduler(processes);
	std::cout << "After heapifying" << std::endl;
	MinHeap<std::unique_ptr<Process>> heap(processes, compareArrivalTime);
	heap.printHeap();
	heap.extractMin();
	std::cout << "After extracting min" << std::endl;
	heap.printHeap();
	heap.insert(std::make_unique<Process>(10, 0, 1));
	std::cout << "After inserting" << std::endl;
	heap.printHeap();
	// scheduler.sortProcessesByArrivalTime();
	// std::cout << "After sorting" << std::endl;
	// for (const auto &process : scheduler.getProcesses())
	// {
	// 	std::cout << *process << std::endl;
	// }
	return 0;
}
