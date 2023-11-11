#include <bits/stdc++.h>
using namespace std;

int FCFS(int reqNum, int head, int *req);
int SSTF(int reqNum, int head, int *req);
int SCAN(int reqNum, int head, int *req);
int CSCAN(int reqNum, int head, int *req);

int main()
{

    int head, reqNum, choice, seekTime, *req;
    string str;
    while (1)
    {
        cout << "\nEnter number of requests in the queue: ";
        cin >> reqNum;
        req = new int[reqNum];
        cout << "\nEnter the request queue: ";
        for (int i = 0; i < reqNum; i++)
        {
            cin >> req[i];
        }

        cout << "\nEnter head position: ";
        cin >> head;

        cout << "\n\n 1. First Come First Serve(FCFS)\n 2. Shortest Seek Time First(SSTF)\n 3. SCAN \n 4. CSCAN \n 5. Exit \nChoose the algorithm to be used: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            seekTime = FCFS(reqNum, head, req);
            break;
        case 2:
            seekTime = SSTF(reqNum, head, req);
            break;
        case 3:
            seekTime = SCAN(reqNum, head, req);
            break;
        case 4:
            seekTime = CSCAN(reqNum, head, req);
            break;
        case 5:
            return 0;
        default:
            cout << "\nWrong Choice!";
        }

        delete (req);
        cout << "\nDo You want to Continue?(Y/n): ";
        cin >> str;
        if (str != "Y")
        {
            return 0;
        }
    }
}

int FCFS(int reqNum, int head, int *req)
{
    int seekTime;
    cout << "\n Current Head   Next Track   Tracks Traversed" << endl;
    cout << "\n     " << head << " \t\t " << req[0] << " \t\t " << abs(head - req[0]);
    seekTime = abs(head - req[0]);
    for (int i = 1; i < reqNum; ++i)
    {
        cout << "\n     " << req[i - 1] << " \t\t " << req[i] << " \t\t " << abs(req[i] - req[i - 1]);
        seekTime += abs(req[i - 1] - req[i]);
    }

    cout << "\nThe Seek Distance for selected algorithm is: " << seekTime;

    cout << "\nThe Average Seek Distance for selected algorithm is: " << seekTime / reqNum;
    return seekTime;
}
int SSTF(int reqNum, int head, int *req)
{

    int seekTime = 0, minDiff = INT32_MAX, minIndex;
    cout << "\n Current Head   Next Track   Tracks Traversed" << endl;
    int n = sizeof(req) / sizeof(req[0]);
    sort(req, req + reqNum);
    for (int i = 0; i < reqNum; i++)
    {
        if (abs(head - req[i]) < minDiff)
        {
            minDiff = abs(head - req[i]);
            minIndex = i;
        }
    }
    if (req[minIndex] < head)
    {

        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);
        for (int j = minIndex; j > 0; j--)
        {
            cout << "\n     " << req[j] << " \t\t " << req[j - 1] << " \t\t " << abs(req[j] - req[j - 1]);
            seekTime += abs(req[j] - req[j - 1]);
        }

        cout << "\n     " << req[0] << " \t\t " << req[minIndex + 1] << " \t\t " << abs(req[0] - req[minIndex + 1]);
        seekTime += abs(req[0] - req[minIndex + 1]);
        for (int k = minIndex + 1; k < reqNum - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }
    }
    else
    {
        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);
        for (int k = minIndex; k < reqNum - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }

        cout << "\n     " << req[reqNum - 1] << " \t\t " << req[minIndex - 1] << " \t\t " << abs(req[reqNum - 1] - req[minIndex - 1]);
        seekTime += abs(req[reqNum - 1] - req[minIndex - 1]);
        for (int j = minIndex; j > 1; j--)
        {
            cout << "\n     " << req[j] << " \t\t " << req[j - 1] << " \t\t " << abs(req[j] - req[j - 1]);
            seekTime += abs(req[j] - req[j - 1]);
        }
    }

    cout << "\nThe Seek Distance for selected algorithm is: " << seekTime;
    cout << "\nThe Average Seek Distance for selected algorithm is: " << seekTime / reqNum;
    return seekTime;
}
int SCAN(int reqNum, int head, int *req)
{
    int dir;
    cout << "\n1. Towards Larger value.\n2. Towards Smaller value.\nEnter Direction: ";
    cin >> dir;
    int seekTime = 0, minDiff = INT32_MAX, minIndex;
    cout << "\n Current Head   Next Track   Tracks Traversed" << endl;
    int n = sizeof(req) / sizeof(req[0]);
    sort(req, req + reqNum);

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

        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);
        for (int k = minIndex; k < reqNum - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }

        cout << "\n     " << req[reqNum - 1] << " \t\t 199"
             << " \t\t " << abs(req[reqNum - 1] - 199);
        seekTime += abs(req[reqNum - 1] - 199);

        cout << "\n     199"
             << " \t\t " << req[minIndex - 1] << " \t\t " << abs(199 - req[minIndex - 1]);
        seekTime += abs(199 - req[minIndex - 1]);
        for (int j = minIndex - 1; j > 0; j--)
        {
            cout << "\n     " << req[j] << " \t\t " << req[j - 1] << " \t\t " << abs(req[j] - req[j - 1]);
            seekTime += abs(req[j] - req[j - 1]);
        }
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
        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);

        for (int j = minIndex; j > 0; j--)
        {
            cout << "\n     " << req[j] << " \t\t " << req[j - 1] << " \t\t " << abs(req[j] - req[j - 1]);
            seekTime += abs(req[j] - req[j - 1]);
        }

        cout << "\n     " << req[0] << " \t\t 0"
             << " \t\t " << abs(req[0] - 0);
        seekTime += abs(req[0] - 0);

        cout << "\n     0\t"
             << " \t\t " << req[minIndex + 1] << " \t\t " << abs(req[minIndex + 1] - 0);
        seekTime += abs(req[minIndex + 1] - 0);

        for (int k = minIndex + 1; k < reqNum - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }
    }

    cout << "\nThe Seek Distance for selected algorithm is: " << seekTime;
    cout << "\nThe Average Seek Distance for selected algorithm is: " << seekTime / reqNum;
    return seekTime;
}
int CSCAN(int reqNum, int head, int *req)
{
    int dir;
    cout << "\n1. Towards Larger value.\n2. Towards Smaller value.\nEnter Direction: ";
    cin >> dir;
    int seekTime = 0, minDiff = INT32_MAX, minIndex;
    cout << "\n Current Head   Next Track   Tracks Traversed" << endl;
    int n = sizeof(req) / sizeof(req[0]);
    sort(req, req + reqNum);

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
        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);
        for (int k = minIndex; k < reqNum - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }

        cout << "\n     " << req[reqNum - 1] << " \t\t 199"
             << " \t\t " << abs(req[reqNum - 1] - 199);
        seekTime += abs(req[reqNum - 1] - 199);

        cout << "\n     199"
             << " \t\t 0"
             << " \t\t " << abs(199 - 0);
        seekTime += abs(199 - 0);

        cout << "\n     0"
             << " \t\t\t " << req[0] << " \t\t " << abs(req[0] - 0);
        seekTime += abs(req[0] - 0);

        for (int k = 0; k < minIndex - 1; k++)
        {
            cout << "\n     " << req[k] << " \t\t " << req[k + 1] << " \t\t " << abs(req[k] - req[k + 1]);
            seekTime += abs(req[k] - req[k + 1]);
        }
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

        cout << "\n     " << head << " \t\t " << req[minIndex] << " \t\t " << abs(head - req[minIndex]);
        seekTime += abs(head - req[minIndex]);

        for (int j = minIndex; j > 0; j--)
        {
            cout << "\n     " << req[j] << " \t\t " << req[j - 1] << " \t\t " << abs(req[j] - req[j - 1]);
            seekTime += abs(req[j] - req[j - 1]);
        }

        cout << "\n     " << req[0] << " \t\t 0"
             << " \t\t " << abs(req[0] - 0);
        seekTime += abs(req[0] - 0);

        cout << "\n     0"
             << " \t\t\t 199"
             << " \t\t " << abs(199 - 0);
        seekTime += abs(199 - 0);

        cout << "\n     199"
             << " \t\t " << req[reqNum - 1] << " \t\t " << abs(199 - req[reqNum - 1]);
        seekTime += abs(199 - req[reqNum - 1]);

        for (int k = reqNum - 1; k > minIndex + 1; k--)
        {

            cout << "\n     " << req[k] << " \t\t " << req[k - 1] << " \t\t " << abs(req[k] - req[k - 1]);
            seekTime += abs(req[k] - req[k - 1]);
        }
    }

    cout << "\nThe Seek Distance for selected algorithm is: " << seekTime;
    cout << "\nThe Average Seek Distance for selected algorithm is: " << seekTime / reqNum;
    return seekTime;
}