# A CPU Scheduling Algorithm Simulator in C++

This repository was a part of my undergraduate coursework.  
It has now been made open-source under the MIT License.

The project simulates the execution of processes on a CPU.

## Usage

Follow the on-screen prompts to provide input.  
The program creates two files:

1. `processes.txt` - Contains the final results when the simulation completes.  
An empty file indicates that no processes have completed execution. Run the program again with a higher simulation time.
2. `status.txt` - Logs the events _(arrival, execution, completion, etc. of processes)_ in the simulator.

## Design

There are 3 types of schedulers implemented in this project:

1. First Come First Serve (FCFS)
2. Round Robin (RR)
3. Completely Fair Scheduler (CFS)

The project uses a [Strategy Pattern](https://en.wikipedia.org/wiki/Strategy_pattern) to implement the schedulers.

## Setting up your workspace

This project has a [.editorconfig file](https://editorconfig.org/) to enforce project level coding standards.  
CLion has built-in support,
VSCode requires [a plugin](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig).

## How to run

This project requires [CMake](https://cmake.org/) to build.
Your IDE (VSCode or CLion) should automatically detect the CMakeLists.txt file and build the project.
Install extensions for CMake support if prompted.  
If you are using the command line, you can run the following commands:

```bash
cmake -B build
cmake --build build --config Debug
```

Then execute the following commands to run the program:

Windows:

```cmd
.\build\executable
```

Linux:

```bash
./build/executable
```

## Generating Documentation

This project uses [Doxygen](https://www.doxygen.nl/index.html) to generate documentation.  
If Doxygen is available on your system,  
You can generate the documentation by running the following command:

```bash
doxygen Doxyfile
```

Once done, you can open the generated documentation by opening the [`docs/index.html`](docs/index.html) file in your browser.

This repository has automated workflow via Github Actions. Documentation is auto-generated.  
Disable Actions on your own fork or delete the [workflows](./.github/workflows) folder if you do not want to be billed.  
This is **not my responsiblity.**
