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

int main()
{
	Process **processes = ProcessCreator::createProcesses(10);
	for (int i = 0; i < 10; i++)
	{
		std::cout << *processes[i] << std::endl;
	}
	return 0;
}
