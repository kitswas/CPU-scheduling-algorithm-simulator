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
#include "process.h"

int main()
{
	Process p(1, 2, 3);
	std::cout << p << std::endl;
	return 0;
}
