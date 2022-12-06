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

int main()
{
	std::vector<std::unique_ptr<Process>> processes = ProcessCreator::createProcesses(10);
	for (const auto &process : processes)
	{
		std::cout << *process << std::endl;
	}
	return 0;
}
