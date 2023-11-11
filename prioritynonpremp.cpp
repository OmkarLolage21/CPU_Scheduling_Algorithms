#include <iostream>
#include <algorithm>

using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

bool comparePriority(const Process &p1, const Process &p2)
{
    return p1.priority < p2.priority;
}

void priorityScheduling(Process *processes, int n)
{
    sort(processes, processes + n, compareArrivalTime);

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; ++i)
    {
        sort(processes + i, processes + n, comparePriority);
        processes[i].waitingTime = (i == 0) ? 0 : processes[i - 1].completionTime;
        processes[i].completionTime = processes[i].waitingTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;
    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime
             << "\t\t" << processes[i].priority << "\t\t" << processes[i].completionTime << "\t\t"
             << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << "\n";
    }

    cout << "\nAverage Waiting Time: " << averageWaitingTime << "\n";
    cout << "Average Turnaround Time: " << averageTurnaroundTime << "\n";
}

int main()
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process *processes = new Process[n];
    for (int i = 0; i < n; ++i)
    {
        processes[i].processID = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }
    priorityScheduling(processes, n);
    delete[] processes;

    return 0;
}
