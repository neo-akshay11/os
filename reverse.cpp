#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    std::cout << "\nInside Reverse Program\n";
    std::cout << "Printing Sorted Array In Reverse Order\n";

    // Print the sorted array in reverse order
    for (int i = 5; i >= 1; --i)
    {
        int x = std::atoi(argv[i]);
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    return 0;
}