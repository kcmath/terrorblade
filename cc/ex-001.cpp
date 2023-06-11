#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

unordered_map<int, int> findConnectedComponents(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    UnionFind uf(numVertices);
    unordered_map<int, int> componentID;

    for (int vertex = 0; vertex < numVertices; ++vertex) {
        for (int neighbor : graph[vertex]) {
            uf.unite(vertex, neighbor);
        }
    }

    int componentCounter = 0;
    for (int vertex = 0; vertex < numVertices; ++vertex) {
        int root = uf.find(vertex);
        if (componentID.find(root) == componentID.end()) {
            componentID[root] = componentCounter++;
        }
        componentID[vertex] = componentID[root];
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

    // Find connected components using Union-Find
    unordered_map<int, int> componentID = findConnectedComponents(graph);

    // Output the vertex tagging
    cout << "Vertex Component ID:" << endl;
    for (int vertex = 0; vertex < numVertices; ++vertex) {
        cout << "Vertex " << vertex << ": Component " << componentID[vertex] << endl;
    }

    return 0;
}

//In this updated code, the UnionFind class represents the Union-Find data structure. The find method finds the root (representative) of a set, and the unite method combines two sets by joining their roots.

//The findConnectedComponents function uses the Union-Find data structure to find the connected components in the graph. It iterates over each vertex and its neighbors, performing the unite operation to merge the sets. Then, it assigns component IDs to the vertices based on their root (representative) in the Union-Find structure. The componentID map stores the mapping between each vertex and its component ID.

//The main function remains the same, and it outputs the vertex tagging with their corresponding component IDs. Now, when you run this code, you should see the vertices tagged with their respective component IDs using the Union-Find data structure.

//Union-Find is particularly efficient when there are a large number of union operations, making it a suitable choice for finding connected components in a graph. It has a time complexity of O(alpha(n)) per operation, where alpha(n) is the inverse Ackermann function and grows very slowly. Therefore, the overall time complexity of finding connected components using Union-Find is approximately O(V + E * alpha(n)), where V is the number of vertices and E is the number of edges in the graph.
