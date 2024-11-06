#include <stdio.h>

int findLRU(int time[], int m)
{
    int minimum = time[0], pos = 0;
    for (int i = 1; i < m; ++i)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int pages[], int frames[], int curr, int n, int m)
{
    int i, j, farthest = curr, pos = -1;
    for (i = 0; i < m; ++i)
    {
        for (j = curr + 1; j < n; ++j)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void printFrames(int frames[], int m, int pageFault)
{
    for (int i = 0; i < m; ++i)
    {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf("%d ", frames[i]);
    }
    if (pageFault)
        printf(" - page fault");
    printf("\n");
}

void FCFS(int pages[], int n, int m)
{
    int frames[m], count = 0, pageFaults = 0;
    for (int i = 0; i < m; ++i)
        frames[i] = -1;

    printf("\nFCFS Page Replacement:\n");
    for (int i = 0; i < n; ++i)
    {
        int found = 0;
        for (int j = 0; j < m; ++j)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            frames[count] = pages[i];
            count = (count + 1) % m;
            pageFaults++;
        }
        printFrames(frames, m, !found);
    }
    printf("FCFS Total Page Faults: %d\n", pageFaults);
}

void LRU(int pages[], int n, int m)
{
    int frames[m], time[m], counter = 0, pageFaults = 0;
    for (int i = 0; i < m; ++i)
    {
        frames[i] = -1; // Initialize frames as empty
        time[i] = 0;    // Initialize time stamps
    }

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; ++i)
    {
        int found = 0;
        // Check if page is already in frames
        for (int j = 0; j < m; ++j)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                time[j] = ++counter; // Update the access time for this page
                break;
            }
        }

        // Page not found in frames (page fault occurs)
        if (!found)
        {
            int pos;
            if (i < m)
            { // Initial loading of pages into empty frames
                pos = i;
            }
            else
            { // All frames are full, use LRU to replace
                pos = findLRU(time, m);
            }
            frames[pos] = pages[i]; // Replace it with the new page
            time[pos] = ++counter;  // Update time for the new page
            pageFaults++;
        }
        printFrames(frames, m, !found); // Print the frames and indicate page fault
    }
    printf("LRU Total Page Faults: %d\n", pageFaults);
}
void Optimal(int pages[], int n, int m)
{
    int frames[m], pageFaults = 0;
    for (int i = 0; i < m; ++i)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; ++i)
    {
        int found = 0;
        for (int j = 0; j < m; ++j)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            if (i < m)
            {
                frames[i] = pages[i];
            }
            else
            {
                int pos = findOptimal(pages, frames, i, n, m);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }
        printFrames(frames, m, !found);
    }
    printf("Optimal Total Page Faults: %d\n", pageFaults);
}

int main()
{
    int n, frameSize;

    printf("Enter the number of page references: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    FCFS(pages, n, frameSize);
    LRU(pages, n, frameSize);
    Optimal(pages, n, frameSize);

    return 0;
}