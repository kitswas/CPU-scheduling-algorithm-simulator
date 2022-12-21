#include "printer.hpp"

int save_processes_to_file(std::vector<std::unique_ptr<Process>> &processes)
{
	std::ofstream processesFile;
	processesFile.open("processes.txt");
	if (!processesFile.is_open())
	{
		std::cout << "Error opening processes file\n";
		return 1;
	}
	else
	{
		std::cout << "Processes file opened successfully\n";
	}
	processesFile << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << std::endl;
	for (auto &process : processes)
	{
		processesFile << process->toString() << "\n";
	}
	processesFile.close();
	return 0;
}
