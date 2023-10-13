#include <iostream>

using namespace std;

bool isSafe(int available[], int maximum[][100], int allocation[][100], int n, int m)
{
    int need[100][100];

    // Calculate the need matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    bool finish[100] = {false};
    int safeSequence[100];
    int work[100];

    // Initialize work with available resources
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found)
        {
            // If no process can be allocated, the system is in an unsafe state
            return false;
        }
    }

    // If all processes have been allocated, the system is in a safe state
    cout << "Safe Sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSequence[i];
        if (i != n - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;

    return true;
}

int main()
{
    int n, m; // Number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    int available[100];
    int maximum[100][100];
    int allocation[100][100];

    cout << "Enter available resources: ";
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
    }

    cout << "Enter maximum demand for each process: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maximum[i][j];
        }
    }

    cout << "Enter current allocation for each process: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    if (isSafe(available, maximum, allocation, n, m))
    {
        cout << "The system is in a safe state." << endl;
    }
    else
    {
        cout << "The system is in an unsafe state." << endl;
    }

    return 0;
}
