class Process
{
private:
	int pid;
	int arrivalTime;
	int burstTime;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
	int responseTime;

public:
	Process(int pid, int arrivalTime, int burstTime);
	~Process();
};

Process::Process(int pid, int arrivalTime, int burstTime) : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime)
{
}

Process::~Process()
{
}
