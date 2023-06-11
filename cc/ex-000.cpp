#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <unordered_map>

using namespace std;

// Recursive DFS to find connected components and tag vertices with component ID
void dfsRecursive(vector<vector<int>>& graph, int vertex, unordered_set<int>& visited, unordered_map<int, int>& componentID, int currentComponentID) {
    visited.insert(vertex);
    componentID[vertex] = currentComponentID;

    for (int neighbor : graph[vertex]) {
        if (visited.find(neighbor) == visited.end()) {
            dfsRecursive(graph, neighbor, visited, componentID, currentComponentID);
        }
    }
}

// Iterative DFS to find connected components and tag vertices with component ID
void dfsIterative(vector<vector<int>>& graph, int startVertex, unordered_set<int>& visited, unordered_map<int, int>& componentID, int currentComponentID) {
    stack<int> stk;
    stk.push(startVertex);

    while (!stk.empty()) {
        int vertex = stk.top();
        stk.pop();

        if (visited.find(vertex) == visited.end()) {
            visited.insert(vertex);
            componentID[vertex] = currentComponentID;

            for (int neighbor : graph[vertex]) {
                if (visited.find(neighbor) == visited.end()) {
                    stk.push(neighbor);
                }
            }
        }
    }
}

// Function to find connected components in a graph and tag vertices with component ID
unordered_map<int, int> findConnectedComponents(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    unordered_set<int> visited;
    unordered_map<int, int> componentID;

    int currentComponentID = 0;

    for (int vertex = 0; vertex < numVertices; ++vertex) {
        if (visited.find(vertex) == visited.end()) {
            // Choose either recursive or iterative version
            // dfsRecursive(graph, vertex, visited, componentID, currentComponentID);
            dfsIterative(graph, vertex, visited, componentID, currentComponentID);
            currentComponentID++;
        }
    }

    return componentID;
}

int main() {
    int numVertices = 9;
    vector<vector<int>> graph(numVertices);

    // Adding edges to the graph
    graph[0] = {1, 2};
    graph[1] = {0, 2};
    graph[2] = {0, 1};
    graph[3] = {4, 5};
    graph[4] = {3, 5};
    graph[5] = {3, 4};
    graph[6] = {7};
    graph[7] = {6};
    graph[8] = {};  // isolated vertex

    // Find connected components using either recursive or iterative version
    unordered_map<int, int> componentID = findConnectedComponents(graph);

    // Output the vertex tagging
    cout << "Vertex Component ID:" << endl;
    for (int vertex = 0; vertex < numVertices; ++vertex) {
        cout << "Vertex " << vertex << ": Component " << componentID[vertex] << endl;
    }

    return 0;
}
