#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

class Graph
{
public:
    Graph(int numNodes) : numNodes(numNodes)
    {
        adjacencyMatrix.resize(numNodes, std::vector<int>(numNodes, 0));
    }

    void addEdge(int from, int to)
    {
        adjacencyMatrix[from][to] = 1;
    }

    bool isCyclicUtil(int v, std::vector<bool> &visited, std::vector<bool> &recStack)
    {
        if (!visited[v])
        {
            visited[v] = true;
            recStack[v] = true;

            for (int i = 0; i < numNodes; ++i)
            {
                if (adjacencyMatrix[v][i] == 1)
                {
                    if (!visited[i] && isCyclicUtil(i, visited, recStack))
                        return true;
                    else if (recStack[i])
                        return true;
                }
            }
        }

        recStack[v] = false;
        return false;
    }

    bool isCyclic()
    {
        std::vector<bool> visited(numNodes, false);
        std::vector<bool> recStack(numNodes, false);

        for (int i = 0; i < numNodes; ++i)
        {
            if (isCyclicUtil(i, visited, recStack))
                return true;
        }

        return false;
    }

private:
    int numNodes;
    std::vector<std::vector<int>> adjacencyMatrix;
};

int main()
{
    int numProcesses, numResources;

    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;

    std::cout << "Enter the number of resources: ";
    std::cin >> numResources;

    Graph graph(numProcesses + numResources);

    // Add edges to the graph based on resource allocation
    for (int i = 0; i < numProcesses; ++i)
    {
        int process, resource;
        std::cout << "Enter the process and resource for allocation (0-indexed): ";
        std::cin >> process >> resource;

        graph.addEdge(process, numProcesses + resource);
    }

    if (graph.isCyclic())
        std::cout << "Deadlock detected!" << std::endl;
    else
        std::cout << "No deadlock detected." << std::endl;

    return 0;
}
