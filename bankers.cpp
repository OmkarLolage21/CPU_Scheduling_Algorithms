#include <iostream>

using namespace std;

void displayTable(int n, int m, int allocation[][100], int maximum[][100], int need[][100])
{
    cout << "\nProcess ID\tAllocated\tMaximum\t\tNeeded" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << maximum[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int available[], int maximum[][100], int allocation[][100], int n, int m)
{
    int need[100][100];

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
            return false;
        }
    }
    displayTable(n, m, allocation, maximum, need);
    cout << "\nSafe Sequence: ";
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
    int n, m;
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
