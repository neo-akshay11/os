#include <sys/types.h> //Importing required libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

void bubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int ch;
    cout << "1.Normal Execution (Sorting) " << endl;
    cout << "2. zombie" << endl;
    cout << "3.orphan" << endl;
    cout << "enter ch" << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
        int n;
        cout << "enter n" << endl;
        n = 5;
        cout << "enter n elements" << endl;
        int arr[5];
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        pid_t id;
        id = fork();
        switch (id)
        {
        case -1:
            cout << "fail" << endl;
            break;
        case 0:
            cout << "child process" << " ";
            cout << "child" << " " << getpid();
            bubble(arr, n);
            break;
        default:
            cout << "parent process" << " ";
            bubble(arr, n);

            cout << "parent" << " " << getpid();

            break;
        }
        break;
    case 2:
        pid_t id1;
        id1 = fork();
        switch (id1)
        {
        case -1:
            cout << "fail" << endl;
            break;
        case 0:
            // cout << "child process" << " ";
            // bubble(arr, n);
            cout << "parent" << " " << getppid();
            cout << "child" << " " << getpid();
            break;
        default:
            // cout << "parent process" << " ";
            //  bubble(arr, n);
            sleep(10);
            cout << "parent" << " " << getpid();
            cout << "child" << " " << id1;

            break;
        }
        break;
    case 3:
        pid_t id2;
        id2 = fork();
        switch (id2)
        {
        case -1:
            cout << "fail" << endl;
            break;
        case 0:
            cout << "child process" << " ";
            // bubble(arr, n);
            sleep(10);
            cout << "parent" << " " << getppid();
            cout << "child" << " " << getpid();
            break;
        default:
            cout << "parent process" << " ";
            // bubble(arr, n);

            cout << "parent" << " " << getpid();
            cout << "child" << " " << id2;

            break;
        }
        break;
    }
}