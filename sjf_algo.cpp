#include <iostream>
#include <limits.h>
using namespace std;
struct Process
{
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wat;
};
void sortProcessesByArrivalTime(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].at > processes[j + 1].at)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
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
        cin >> processes[i].at;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].bt;
        processes[i].rt = processes[i].bt;
    }
    // Sort processes by arrival time
    sortProcessesByArrivalTime(processes, n);

    int current_time = 0;
    int completed = 0;
    int sequence[n];

    while (completed < n)
    {
        int shortest_job = -1;
        int shortest_time = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= current_time && processes[i].rt < shortest_time && processes[i].rt > 0)
            {
                shortest_job = i;
                shortest_time = processes[i].rt;
            }
        }

        if (shortest_job == -1)
        {
            current_time++;
        }
        else
        {
            processes[shortest_job].rt--;
            current_time++;
            if (processes[shortest_job].rt == 0)
            {
                completed++;
                int ct = current_time;
                processes[shortest_job].ct = ct;
                processes[shortest_job].tat = ct - processes[shortest_job].at;
                processes[shortest_job].wat = processes[shortest_job].tat - processes[shortest_job].bt;
                sequence[completed - 1] = processes[shortest_job].id;
            }
        }
    }
    cout << "\n\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        int index = sequence[i] - 1; // Get the index of the process based on scheduling sequence
        cout << "P" << processes[index].id << "\t" << processes[index].at << "\t\t" << processes[index].bt << "\t\t"
             << processes[index].ct << "\t\t" << processes[index].tat << "\t\t" << processes[index].wat << "\n";
    }
    return 0;
}
