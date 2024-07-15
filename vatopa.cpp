#include <iostream>
#include <vector>

class AddressTranslator
{
public:
    AddressTranslator(int pageSize, int numFrames) : pageSize(pageSize), numFrames(numFrames)
    {
        pageTable.resize(numFrames, -1); // Initialize page table with invalid entries
    }

    void setPageTableEntry(int pageNumber, int frameNumber)
    {
        if (pageNumber >= 0 && pageNumber < numFrames)
        {
            pageTable[pageNumber] = frameNumber;
        }
    }

    int translateAddress(int logicalAddress)
    {
        int pageNumber = logicalAddress / pageSize;
        int offset = logicalAddress % pageSize;

        if (pageNumber < 0 || pageNumber >= numFrames || pageTable[pageNumber] == -1)
        {
            std::cerr << "Invalid page number or page table entry not found. Invalid address." << std::endl;
            return -1; // Error code
        }

        int frameNumber = pageTable[pageNumber];
        int physicalAddress = (frameNumber * pageSize) + offset;
        return physicalAddress;
    }

private:
    int pageSize;
    int numFrames;
    std::vector<int> pageTable;
};

int main()
{
    // Assume a system with 4 KB page size and 8 frames in the physical memory
    AddressTranslator translator(4096, 8);

    // Set page table entries (simulating address translation)
    translator.setPageTableEntry(0, 1);
    translator.setPageTableEntry(1, 2);
    translator.setPageTableEntry(2, 3);

    // Example logical address
    int logicalAddress;
    std::cout << "Enter a logical address: ";
    std::cin >> logicalAddress;

    // Translate the logical address to a physical address
    int physicalAddress = translator.translateAddress(logicalAddress);

    if (physicalAddress != -1)
    {
        std::cout << "Physical address: " << physicalAddress << std::endl;
    }

    return 0;
}
