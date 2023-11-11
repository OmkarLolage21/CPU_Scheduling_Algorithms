#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int WaitingTime;
    int TAtime;
    int RespTime;
    int fs = -1;
};

bool compareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes, processes + n, compareArrivalTime);

    int currentTime = 0;
    int completed = 0;
    int i = 0, j = 0;
    cout << "\nGantt Chart:\n\n";
    cout << "|";
    while (completed < n)
    {
        int shortestProcess = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0)
            {
                shortestTime = processes[i].remainingTime;
                shortestProcess = i;
            }
        }

        if (shortestProcess == -1)
        {
            cout << "  Idle | ";
            currentTime++;
        }
        else
        {
            processes[shortestProcess].remainingTime--;
            cout << "  P" << processes[shortestProcess].id << "  | ";
            if (processes[shortestProcess].fs == -1)
            {
                processes[shortestProcess].fs = currentTime;
            }
            currentTime++;
            if (processes[shortestProcess].remainingTime == 0)
            {
                processes[shortestProcess].completionTime = currentTime;
                completed++;
            }
        }
    }
    while (j < n)
    {
        processes[j].TAtime = processes[j].completionTime - processes[j].arrivalTime;
        processes[j].WaitingTime = processes[j].TAtime - processes[j].burstTime;
        processes[j].RespTime = processes[j].fs - processes[j].arrivalTime;
        j++;
    }
    cout << "\n";
    cout << i;
    i++;
    while (i <= currentTime)
    {
        cout << "\t" << i;
        i++;
    }

    cout << "\n\nProcess\t  Arrival Time\t  Burst Time\tCompletion Time\t\tAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].id << "\t\t " << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].TAtime << "\t" << processes[i].WaitingTime << "\t" << processes[i].RespTime << endl;
    }

    return 0;
}
