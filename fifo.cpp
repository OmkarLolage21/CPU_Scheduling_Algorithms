#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter the number of frames: ";
    cin >> n;

    int frames[n];
    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
    }

    int frameIndex = 0;

    int numPageReferences;
    cout << "Enter the number of page references: ";
    cin >> numPageReferences;

    cout << "Enter the page reference string: ";
    int pageReference;
    int pageFaults = 0;
    int pageHits = 0;
    for (int i = 0; i < numPageReferences; i++)
    {
        cin >> pageReference;
        bool pageFound = false;

        for (int j = 0; j < n; j++)
        {
            if (frames[j] == pageReference)
            {
                pageFound = true;
                pageHits++;
                break;
            }
        }

        if (!pageFound)
        {
            frames[frameIndex] = pageReference;
            frameIndex = (frameIndex + 1) % n;
            pageFaults++;
        }
    }

    cout << "Total page hits: " << pageHits << endl;
    cout << "Total page faults: " << pageFaults << endl;
    double pageHitRatio = static_cast<double>(pageHits) / numPageReferences;
    cout << "Page Hit Ratio: " << pageHitRatio << endl;

    return 0;
}
