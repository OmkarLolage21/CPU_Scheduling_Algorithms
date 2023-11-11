#include <iostream>

struct Block
{
    int size;
    bool allocated;
};

void firstFit(Block *memory, int numBlocks, int processSize)
{
    for (int i = 0; i < numBlocks; ++i)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = true;
            std::cout << "Process allocated to Block " << i + 1 << std::endl;
            return;
        }
    }

    std::cout << "No suitable block found for the process." << std::endl;
}

int main()
{
    int numBlocks;

    std::cout << "Enter the number of memory blocks: ";
    std::cin >> numBlocks;

    Block *memory = new Block[numBlocks];
    for (int i = 0; i < numBlocks; ++i)
    {
        std::cout << "Enter the size of Block " << i + 1 << ": ";
        std::cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int numProcesses;

    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i)
    {
        int processSize;
        std::cout << "Enter the size of Process " << i + 1 << ": ";
        std::cin >> processSize;
        firstFit(memory, numBlocks, processSize);
    }
    delete[] memory;

    return 0;
}
