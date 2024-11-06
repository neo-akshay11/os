#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    vector<int> arr(5);

    cout << "\nEnter Five Integers To Be Sorted \n";
    for (int i = 0; i < 5; ++i)
    {
        cout << "Enter Integer " << i + 1 << " : ";
        cin >> arr[i];
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        cerr << "Error In Forking The Process!\n";
    }
    else if (pid == 0)
    {
        // Child process
        cout << "\nInside Child Process \n";
        bubbleSort(arr);

        cout << "Array Sorted By Child Process: ";
        for (int num : arr)
        {
            cout << num << " ";
        }
        cout << "\n";

        vector<char *> sarr(7);
        sarr[0] = "./reverse";
        sarr[6] = nullptr;

        // Convert integers to C-style strings using std::to_string and store them in sarr
        for (int i = 0; i < 5; ++i)
        {
            string numStr = to_string(arr[i]);
            sarr[i + 1] = new char[numStr.size() + 1];
            strcpy(sarr[i + 1], numStr.c_str()); // Copy the string to a char array
        }

        execv("./reverse", sarr.data());

        // Free allocated memory if execv fails
        for (int i = 1; i < 6; ++i)
        {
            delete[] sarr[i];
        }

        cerr << "Error executing ./reverse\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        cout << "\nInside Parent Process \n";
        cout << "Waiting For Child Process To Terminate...\n";
        wait(nullptr);
        cout << "Execution Of Child Process Has Been Completed\n";
        cout << "Ending Parent Process Now\n\n";
    }

    return 0;
}