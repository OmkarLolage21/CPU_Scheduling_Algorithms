#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
void difference(int request[], int head, int diff[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - request[i]);
    }
}
int findMIN(int diff[][2], int n)
{
    int index = -1;
    int minimum = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}
void shortestSeekTimeFirst(int request[], int head, int n)
{
    if (n == 0)
    {
        return;
    }
    int diff[n][2] = {{0, 0}};
    int count = 0;
    int sequence[n + 1] = {0};

    for (int i = 0; i < n; i++)
    {
        sequence[i] = head;
        difference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
        count += diff[index][0];
        head = request[index];
    }
    sequence[n] = head;
    cout << "Total number of seek operations = "
         << count << endl;
    cout << "Seek sequence is : "
         << "\n";
    for (int i = 0; i <= n; i++)
    {
        cout << sequence[i] << "\n";
    }
}
int main()
{
    int n = 9;
    int proc[n] = {55, 185, 396, 455, 512, 27, 220, 315, 86};
    shortestSeekTimeFirst(proc, 100, n);
    return 0;
}