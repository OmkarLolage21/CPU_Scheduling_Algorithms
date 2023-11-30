#include <iostream>
#include <stdlib.h>
using namespace std;
class Process
{
    int id, bt, at, ct, tat, wt;

public:
    void input(Process *, int);
    void calc(Process *, int);
    void show(Process *, int);
    void sort(Process *, int);
    void ganntchart(Process *, int);
};
int main()
{
    int n;
    cout << "\nEnter the no of processes in your system:\n";
    cin >> n;
    Process *p = new Process[n];
    Process f;
    f.input(p, n);
    f.sort(p, n);
    f.calc(p, n);
    f.show(p, n);
    f.ganntchart(p, n);
    return 0;
}
void Process::input(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter arrival time for process " << i + 1 << ":\n";
        cin >> p[i].at;
        cout << "\nEnter burst time for process " << i + 1 << ":\n";
        cin >> p[i].bt;
        p[i].id = i + 1;
    }
}
void Process::calc(Process *p, int n)
{
    int sum = 0;
    sum = sum + p[0].at;
    for (int i = 0; i < n; i++)
    {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (sum < p[i + 1].at)
        {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}
void Process::sort(Process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                // int temp;
                // // sorting burst times
                // temp = p[j].bt;
                // p[j].bt = p[j + 1].bt;
                // p[j + 1].bt = temp;
                // // sorting arrival times
                // temp = p[j].at;
                // p[j].at = p[j + 1].at;
                // p[j + 1].at = temp;
                // // sorting their respective IDs
                // temp = p[j].id;
                // p[j].id = p[j + 1].id;
                // p[j + 1].id = temp;
                swap(p[j], p[j + 1]);
            }
        }
    }
}
void Process::show(Process *p, int n)
{
    cout << "Process\tArrival\tBurst\tCompletion\tTurn Around\tWaiting\n";
    for (int i = 0; i < n; i++)
    {
        cout << " P" << p[i].id << "\t " << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t\t" << p[i].tat << "\t\t" << p[i].wt << "\n";
    }
}
void Process::ganntchart(Process *p, int n)
{
    cout << "---------"
         << "---------"
         << "---------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "| "
             << " P" << p[i].id << "   ";
    }
    cout << "|\n";
    cout << "---------"
         << "---------"
         << "---------\n";
    cout << p[0].at << "\t";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].ct << "\t";
    }
}