#ifndef SAVE_PROCESSES_TO_FILE
#define SAVE_PROCESSES_TO_FILE

#include <fstream>
#include <vector>
#include <memory>
#include "process.hpp"

int save_processes_to_file(std::vector<std::unique_ptr<Process>> &processes);

#endif // SAVE_PROCESSES_TO_FILE
