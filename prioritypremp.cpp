#include <iostream>
#include <limits.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int responseTime;
    int waitingTime;
};

void sortByPriority(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority < processes[j + 1].priority)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
}

int findProcessWithHighestPriority(Process processes[], int n, int currentTime)
{
    int highestPriorityIndex = -1;
    int highestPriority = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
        {
            if (processes[i].priority > highestPriority)
            {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }
    }

    return highestPriorityIndex;
}

void preemptivePriorityScheduling(Process processes[], int n)
{
    int currentTime = 0;

    while (true)
    {
        int processIndex = findProcessWithHighestPriority(processes, n, currentTime);

        if (processIndex == -1)
        {
            // No processes are ready to execute
            currentTime++;
        }
        else
        {
            // Execute the process with the highest priority
            processes[processIndex].remainingTime--;

            if (processes[processIndex].responseTime == -1)
            {
                processes[processIndex].responseTime = currentTime - processes[processIndex].arrivalTime;
            }

            currentTime++;

            if (processes[processIndex].remainingTime == 0)
            {
                // Process is completed
                processes[processIndex].completionTime = currentTime;
                processes[processIndex].turnaroundTime = processes[processIndex].completionTime - processes[processIndex].arrivalTime;
                processes[processIndex].waitingTime = processes[processIndex].turnaroundTime - processes[processIndex].burstTime;

                cout << "| " << processes[processIndex].id << "\t| " << processes[processIndex].arrivalTime << "\t| "
                     << processes[processIndex].burstTime << "\t| " << processes[processIndex].completionTime << "\t| "
                     << processes[processIndex].turnaroundTime << "\t| " << processes[processIndex].responseTime << "\t| "
                     << processes[processIndex].waitingTime << "\t|" << endl;
            }
        }

        bool allProcessesCompleted = true;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0)
            {
                allProcessesCompleted = false;
                break;
            }
        }

        if (allProcessesCompleted)
        {
            break;
        }
    }
}

int main()
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;

        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].responseTime = -1;
        processes[i].waitingTime = 0;
    }

    // Sort processes by priority
    sortByPriority(processes, n);

    // Display table headers
    cout << "| PID\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Response Time\t| Waiting Time\t|" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    // Run preemptive priority scheduling algorithm
    preemptivePriorityScheduling(processes, n);

    return 0;
}
