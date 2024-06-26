#include <iostream>
#include <cstdio>
#include "vector.h"
#include "queue.h"

#define GREEDY 'g'
#define LF 'l'
using namespace std;

// structure used in assigning sides for bipartition representing single vertex
struct Vertex
{
    int index; // vertex index
    char side; // side to which it is assigned (A or B)

    // default constructor
    Vertex() : index(0), side(' ') {}

    Vertex(int i, char s) : index(i), side(s) {}
};

void insertionSortByDegree(int* degrees, int* indices, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int keyDegree = degrees[i];
        int keyIndex = indices[i];
        int j = i - 1;

        while (j >= 0 && (degrees[j] < keyDegree || (degrees[j] == keyDegree && indices[j] > keyIndex)))
        {
            degrees[j + 1] = degrees[j];
            indices[j + 1] = indices[j];
            j = j - 1;
        }
        degrees[j + 1] = keyDegree;
        indices[j + 1] = keyIndex;
    }
}

// function to swap two integers
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}


void heapify(vector<int>& arr, int n, int i)
{
    int largest = i; // largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // if left child is larger than root
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // if right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // if largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// function to perform heap sort
void heapSort(vector<int>& arr, int n)
{
    // build heap - rearrange array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // one by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // move current root to end
        swap(arr[0], arr[i]);

        // call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int getNumber() 
{
    int number = 0;
    char ch = static_cast<char>(getchar());
    while (ch < '0' || ch > '9') 
    {
        ch = static_cast<char>(getchar());
    }
    while (ch >= '0' && ch <= '9') 
    {
        number = number * 10 + (ch - '0');
        ch = static_cast<char>(getchar());
    }
    return number;
}

// Function to perform Depth First Search (DFS) to count connected components
void DFS(vector<vector<int>>& adjacencyList, vector<bool>& visited, int vertex, int& count) 
{
    visited[vertex] = true;
    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor]) 
        {
            count++;
            DFS(adjacencyList, visited, neighbor, count);
        }
    }
}

// Function to perform DFS and assign component sizes
void DFS_2(vector<vector<int>>& adjacencyList, vector<bool>& visited, int vertex, vector<int>& componentSize, int currentSize) 
{
    visited[vertex] = true;
    componentSize[vertex] = currentSize;
    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor]) 
        {
            DFS_2(adjacencyList, visited, neighbor, componentSize, currentSize);
        }
    }
}


// Function to find connected components in a graph and assign sizes to each component
int findComponents(vector<vector<int>>& adjacencyList, int vertices, vector<int>& componentSize)
{
    int components = 0; // number of connected components
    vector<int> sizes; // sizes of individual components
    vector<bool> visited(vertices + 1, false); // visited vertices

    // Iterate over each vertex
    for (int i = 1; i <= vertices; ++i)
    {
        if (!visited[i]) // vertex is not visited yet
        {
            int count = 0; // size of the current component
            DFS(adjacencyList, visited, i, count); // DFS  to count vertices in the component
            ++components;
            sizes.push_back(count); // size of the current component
        }
    }
    // reset vector for second DFS
    vector<bool> visited2(vertices + 1, false);

    int countCurrentComponent = 0; // track the current component processed

    for (int i = 1; i <= vertices; ++i)
    {
        if (!visited2[i])
        {
            // DFS to assign component sizes
            DFS_2(adjacencyList, visited2, i, componentSize, sizes[countCurrentComponent]);
            countCurrentComponent++; // next component
        }
    }

    return components; // number of connected components
}



// Function to assign sides to vertices
bool assignSides(vector<vector<int>>& adjacencyList, vector<Vertex>& vertices, int vertex, char side)
{
    vertices[vertex].side = side; // assign side to the current vertex
    for (int neighbor : adjacencyList[vertex])
    {
        // check if the neighbor has a side assigned
        if (vertices[neighbor].side == side)
        {
            // if does its not bipertite
            return false;
        }
        else if (vertices[neighbor].side == ' ')
        {
            // if doesnt have side assigned
            if (!assignSides(adjacencyList, vertices, neighbor, (side == 'A') ? 'B' : 'A'))
            {
                return false; // recursion
            }
        }
    }
    return true; //bipartite
}


// Function to check if a graph is bipartite
bool isBipartite(vector<vector<int>>& adjacencyList, int vertices)
{
    vector<Vertex> verticesInfo;

    // dummy vertex 0 for better indexing
    verticesInfo.push_back(Vertex(0, ' '));

    // initialize verticesInfo
    for (int i = 1; i <= vertices; ++i)
    {
        verticesInfo.push_back(Vertex(i, ' '));
    }

    for (int i = 1; i <= vertices; ++i)
    {
        // if vertex has not been assigned a side
        if (verticesInfo[i].side == ' ')
        {
            //try assign sides starting with side A
            if (!assignSides(adjacencyList, verticesInfo, i, 'A'))
            {
                return false; // not bipartite
            }
        }
    }
    return true;
}

// Function to calculate the complement of edges in a graph
long long calculateComplementEdges(vector<vector<int>>& adjacencyList, int vertices)
{
    long long totalEdges = 0;
    for (int i = 1; i <= vertices; ++i)
    {
        totalEdges += adjacencyList[i].size(); // summing all edges
    }
    totalEdges /= 2; // dividing by 2 to avoid double counting each edge

    long long completeGraphEdges = static_cast<long long>(vertices) * (vertices - 1) / 2;

    long long complementEdges = completeGraphEdges - totalEdges;

    return complementEdges;
}

// Graph coloring
void coloring(vector<vector<int>>& adjacencyList, int vertices, char coloringType)
{
    // intialize result with all colored to -1 which indicates no assigned color
    vector<int> result(vertices + 1, -1);

    // track the availability of colors for vertices
    vector<bool> available(vertices + 1, true);

    // arrays to store degrees of vertices and their original indices
    int* degrees = new int[vertices];
    int* indices = new int[vertices];

    // computing degrees of vertices and initializing indices
    for (int i = 1; i <= vertices; ++i)
    {
        degrees[i - 1] = adjacencyList[i].size();
        indices[i - 1] = i;
    }

    // sorting by degrees for LF coloring
    if (coloringType == 'l')
    {
        insertionSortByDegree(degrees, indices, vertices);
    }

    // assign colors to vertices in sorted order
    for (int i = 0; i < vertices; ++i)
    {
        int u = indices[i]; // current vertex

        // mark colors of adjacent vertices as unavailable
        for (int adj : adjacencyList[u])
        {
            if (result[adj] != -1)
            {
                available[result[adj]] = false;
            }
        }

        // first avaliable color
        int cr;
        for (cr = 1; cr <= vertices; ++cr)
        {
            if (available[cr])
            {
                break;
            }
        }

        result[u] = cr;

        // reseting avaliable colors for the next iteration
        for (int adj : adjacencyList[u])
        {
            if (result[adj] != -1)
            {
                available[result[adj]] = true;
            }
        }
    }
    for (int i = 1; i <= vertices; ++i)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    delete[] degrees;
    delete[] indices;
}

// Function to calculate eccentricity for each vertex
vector<int> calculateEccentricities(vector<vector<int>>& adjacencyList, int vertices, vector<int>& componentSizes)
{
    // vector to store eccentricities for each vertex
    vector<int> eccentricities(vertices + 1, 0);

    // iterating over each vertex to calculate its eccentricity
    for (int start = 1; start <= vertices; ++start)
    {
        // if no neighbors - eccentricity is 0
        if (adjacencyList[start].empty())
        {
            eccentricities[start] = 0;
            continue;
        }

        //  queue for BFS traversal and a vector to store distances from the start vertex
        Queue queue(componentSizes[start] + 1);
        vector<int> distance(vertices + 1, INT_MAX);
        distance[start] = 0; // distance to the start vertex is 0
        queue.push(start);
        int count = 0; // tracking the number of visited vertices
        int maxDistance = 0; // max distance using DFS

        // BFS until all are visited
        while (count < componentSizes[start])
        {
            int v = queue.pop(); // pop front vertex from the queue
            for (int neighbor : adjacencyList[v])
            {
                // if neighbor vertex has not been visited update distance and queue it
                if (distance[neighbor] == INT_MAX)
                {
                    distance[neighbor] = distance[v] + 1;
                    maxDistance = distance[v] + 1; // update max distance
                    queue.push(neighbor);
                    count++;
                }
            }
        }
        eccentricities[start] = maxDistance;
    }

    return eccentricities;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    const int graphs = getNumber();

    for (int graph = 0; graph < graphs; ++graph)
    {
        const int vertices = getNumber();

        vector<vector<int>> adjacencyList(vertices + 1); // +1 to handle 1-based indexing

        for (int i = 1; i <= vertices; ++i)
        {
            const int edges = getNumber();
            for (int j = 0; j < edges; ++j)
            {
                int v = getNumber();
                adjacencyList[i].push_back(v);
            }
        }

        // Degree Sequence
        vector<int> Degrees(vertices + 1);
        for (int i = 1; i <= vertices; ++i)
        {
            Degrees[i] = adjacencyList[i].size();
        }
        // Sorting to show degrees in descending order
        heapSort(Degrees, vertices + 1);

        // Print the sorted degree sequence
        for (int i = vertices; i >= 1; --i)
        {
            printf("%d ", Degrees[i]);
        }
        printf("\n");

        // Number of Components
        vector<int> compontentSize(vertices + 1);
        printf("%d\n", findComponents(adjacencyList, vertices, compontentSize));

        // Bipartiteness
        if (isBipartite(adjacencyList, vertices))
        {
            printf("T\n");
        }
        else
        {
            printf("F\n");
        }

        // The Eccentricity of Vertices (within the Components)
        vector<int> eccentricities = calculateEccentricities(adjacencyList, vertices, compontentSize);
        for (int i = 1; i <= vertices; ++i)
        {
            printf("%d ", eccentricities[i]);
        }
        printf("\n");

        // Planarity
        printf("?\n");

        // Greedy Coloring
        coloring(adjacencyList, vertices, GREEDY);

        // LF Coloring
        coloring(adjacencyList, vertices, LF);

        // SLF Coloring
        printf("?\n");

        // Number of C4 Subgraphs
        printf("?\n");

        // Number of the Graph Complement's Edges
        long long complementEdges = calculateComplementEdges(adjacencyList, vertices);
        printf("%lld\n", complementEdges);
    }
    return 0;
}

