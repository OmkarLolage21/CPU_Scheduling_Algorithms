#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
void SSTF(int *req, int reqNum, int head);
void CSCAN(int req[], int reqNum, int head, int disk_size);
int main()
{
    int reqNum;
    cout << "Enter the number of requests : ";
    cin >> reqNum;
    int *req = new int[reqNum];
    int disk_size;
    cout << "Enter the disk size : ";
    cin >> disk_size;
    cout << "Enter the requests : ";
    for (int i = 0; i < reqNum; i++)
    {
        cin >> req[i];
    }

    int ch;
    int head;
    cout << "Enter the initial head position : ";
    cin >> head;
    cout << "Enter the choice  : ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        SSTF(req, reqNum, head);
        break;
    case 2:
        CSCAN(req, reqNum, head, disk_size);
        break;
    default:
        break;
    }
    return 0;
}
void SSTF(int *req, int reqNum, int head)
{
    int seekTime = 0, minDiff = INT_MAX, minIndex = -1;
    sort(req, req + reqNum);
    int n = sizeof(req) / sizeof(req[0]);
    cout << "Current Track"
         << "\t"
         << "Next Track"
         << "Tracks Traversed\n";
    sort(req, req + reqNum);
    while (reqNum > 0)
    {
        int minDiff = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < reqNum; i++)
        {
            int diff = abs(head - req[i]);
            if (diff < minDiff)
            {
                minDiff = diff;
                minIndex = i;
            }
        }
        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << minDiff;
        seekTime += minDiff;
        head = req[minIndex];
        for (int i = minIndex; i < reqNum - 1; i++)
        {
            req[i] = req[i + 1];
        }

        reqNum--;
    }
    cout << "\nTotal seek operations performed : " << seekTime << endl;
}
void CSCAN(int req[], int reqNum, int head, int disk_size)
{
    int seekTime = 0, minDiff = INT_MAX, minIndex = -1;
    sort(req, req + reqNum);
    int n = sizeof(req) / sizeof(req[0]);
    int dir;
    cout << "Enter the direction  1.Towards Larger Value 2. Towards smaller value : " << endl;
    cin >> dir;
    cout << "Current Track"
         << "\t"
         << "Next Track"
         << "Tracks Traversed\n";
    if (dir == 1)
    {
        for (int i = 0; i < reqNum; i++)
        {
            if (req[i] > head)
            {
                minIndex = i;
                break;
            }
        }
        cout << head << "\t\t" << req[minIndex] << "\t\t" << abs(head - req[minIndex]) << "\n";
        seekTime += abs(head - req[minIndex]);
        for (int k = minIndex + 1; k < reqNum; k++)
        {
            cout << req[k - 1] << "\t\t" << req[k] << "\t\t" << abs(req[k - 1] - req[k]) << "\n";
            seekTime += abs(req[k - 1] - req[k]);
        }

        cout << req[reqNum - 1] << "\t\t" << disk_size << "\t\t" << abs(req[reqNum - 1] - disk_size) << "\n";
        seekTime += abs(req[reqNum - 1] - disk_size);

        cout << disk_size << "\t\t"
             << "0"
             << "\t\t" << abs(disk_size - 0) << "\n";
        seekTime += abs(disk_size - 0);

        cout << "0"
             << "\t\t" << req[0] << "\t\t" << abs(req[0] - 0) << "\n";
        seekTime += abs(req[0] - 0);
        for (int i = 1; i < minIndex; i++)
        {
            cout << req[i - 1] << "\t\t" << req[i] << "\t\t" << abs(req[i - 1] - req[i]) << "\n";
            seekTime += abs(req[i - 1] - req[i]);
        }
        cout << "Total seek operations performed : " << seekTime << endl;
    }
    else
    {
        for (int i = 0; i < reqNum; i++)
        {
            if (req[i] > head)
            {
                minIndex = i - 1;
                break;
            }
        }
        cout << head << "\t\t" << req[minIndex] << "\t\t" << abs(head - req[minIndex]) << "\n";
        seekTime += abs(head - req[minIndex]);
        for (int j = minIndex; j > 0; j--)
        {
            cout << req[j] << "\t\t" << req[j - 1] << "\t\t" << abs(req[j] - req[j - 1]) << "\n";
            seekTime += abs(req[j] - req[j - 1]);
        }
        cout << req[0] << "\t\t"
             << "0"
             << "\t\t" << abs(req[0] - 0) << "\n";
        seekTime += abs(req[0] - 0);

        cout << "0"
             << "\t\t" << disk_size << "\t\t" << abs(disk_size - 0) << "\n";
        seekTime += abs(disk_size - 0);

        cout << disk_size << "\t\t" << req[reqNum - 1] << "\t\t" << abs(req[reqNum - 1] - disk_size) << "\n";
        seekTime += abs(req[reqNum - 1] - disk_size);
        for (int i = reqNum - 1; i > minIndex + 1; i--)
        {
            cout << req[i] << "\t\t" << req[i - 1] << "\t\t" << abs(req[i] - req[i - 1]) << "\n";
            seekTime += abs(req[i] - req[i - 1]);
        }
        cout << "Total seek operations performed : " << seekTime << endl;
    }
}