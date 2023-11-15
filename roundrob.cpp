#include <iostream>
#include <string>

using namespace std;

void queueUpdation(int queue[], int n, int maxProccessIndex)
{
    int zeroIndex;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] == 0)
        {
            zeroIndex = i;
            break;
        }
    }
    queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int queue[], int n)
{
    for (int i = 0; (i < n - 1) && (queue[i + 1] != 0); i++)
    {
        int temp = queue[i];
        queue[i] = queue[i + 1];
        queue[i + 1] = temp;
    }
}

void checkNewArrival(int timer, int arrival[], int n, int &maxProccessIndex, int queue[])
{
    if (timer <= arrival[n - 1])
    {
        bool newArrival = false;
        for (int j = (maxProccessIndex + 1); j < n; j++)
        {
            if (arrival[j] <= timer)
            {
                if (maxProccessIndex < j)
                {
                    maxProccessIndex = j;
                    newArrival = true;
                }
            }
        }
        if (newArrival)
            queueUpdation(queue, n, maxProccessIndex);
    }
}

// Driver Code
int main()
{
    int n, tq, timer = 0, maxProccessIndex = 0;
    float avgWait = 0, avgTT = 0;
    cout << "\nEnter the time quanta : ";
    cin >> tq;
    cout << "\nEnter the number of processes : ";
    cin >> n;
    const int maxProcesses = 20; // Assuming a maximum of 100 processes
    string processNames[maxProcesses];
    int arrival[maxProcesses], burst[maxProcesses], wait[maxProcesses], turn[maxProcesses], queue[maxProcesses], temp_burst[maxProcesses], completion[maxProcesses];
    bool complete[maxProcesses];

    cout << "\nEnter the arrival time of the processes : ";
    for (int i = 0; i < n; i++)
        cin >> arrival[i];

    cout << "\nEnter the burst time of the processes : ";
    for (int i = 0; i < n; i++)
    {
        cin >> burst[i];
        temp_burst[i] = burst[i];
        processNames[i] = "P" + to_string(i + 1);
    }

    for (int i = 0; i < n; i++)
    {
        complete[i] = false;
        queue[i] = 0;
        completion[i] = 0;
    }
    while (timer < arrival[0])
        timer++;
    queue[0] = 1;

    const int maxScheduleSize = maxProcesses * 20;
    string schedule[maxScheduleSize];
    int scheduleIndex = 0;

    while (true)
    {
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (temp_burst[i] != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            break;

        for (int i = 0; (i < n) && (queue[i] != 0); i++)
        {
            int ctr = 0;
            while ((ctr < tq) && (temp_burst[queue[0] - 1] > 0))
            {
                temp_burst[queue[0] - 1] -= 1;
                timer += 1;
                ctr++;
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
                schedule[scheduleIndex++] = processNames[queue[0] - 1];
            }
            if ((temp_burst[queue[0] - 1] == 0) && (complete[queue[0] - 1] == false))
            {
                completion[queue[0] - 1] = timer;
                turn[queue[0] - 1] = completion[queue[0] - 1] - arrival[queue[0] - 1];
                wait[queue[0] - 1] = turn[queue[0] - 1] - burst[queue[0] - 1];
                complete[queue[0] - 1] = true;
            }
            bool idle = true;
            if (queue[n - 1] == 0)
            {
                for (int i = 0; i < n && queue[i] != 0; i++)
                {
                    if (complete[queue[i] - 1] == false)
                    {
                        idle = false;
                    }
                }
            }
            else
                idle = false;

            if (idle)
            {
                timer++;
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
            }
            queueMaintainence(queue, n);
        }
    }

    cout << "\nScheduling Sequence: ";
    for (int i = 0; i < scheduleIndex; i++)
    {
        cout << schedule[i];
        if (i < scheduleIndex - 1)
        {
            cout << "->";
        }
    }

    cout << "\n\nProgram No.\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnAround Time"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processNames[i] << "\t\t" << arrival[i] << "\t\t"
             << burst[i] << "\t\t" << completion[i] << "\t\t" << wait[i] << "\t\t" << turn[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        avgWait += wait[i];
        avgTT += turn[i];
    }
    cout << "\nAverage wait time : " << (avgWait / n)
         << "\nAverage Turn Around Time : " << (avgTT / n);

    return 0;
}
