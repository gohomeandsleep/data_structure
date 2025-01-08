#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Edge3 {
public:
    int src, dest, weight;

    Edge3() {}

    Edge3(int s, int d, int w) : src(s), dest(d), weight(w) {}

    bool operator<(const Edge3& e) const {
        return weight < e.weight;
    }

    friend ostream& operator<<(ostream& os, const Edge3& edge) {
        os << "<" << edge.src << ", " << edge.dest << ", " << edge.weight << ">";
        return os;
    }
};

class Graph_MST {
public:
    int n;
    vector<list<Edge3>> adjacencyList;

    Graph_MST(int nodes) : n(nodes), adjacencyList(nodes) {}

    void insertEdge3(int src, int dest, int weight) {
        adjacencyList[src].emplace_back(src, dest, weight);
        // Uncomment if undirected graph
        // adjacencyList[dest].emplace_back(dest, src, weight);
    }

    void displayAdjacencyLists() {
        for (int i = 0; i < n; i++) {
            cout << i << " -> ";
            for (const auto& edge : adjacencyList[i]) {
                cout << edge << " ";
            }
            cout << endl;
        }
    }
};

class Sets {
public:
    vector<int> parent;

    Sets(int n) : parent(n, -1) {}

    int find(int i) {
        
    }

    void unionSets(int x, int y) {
        
    }
};

void KruskalMST(Graph_MST& graph) {
    vector<Edge3> listEdges;

    // Add all edges from adjacency lists to listEdges
    

    // Sort edges by weight
    sort(listEdges.begin(), listEdges.end());

    // Initialize Disjoint Sets for Kruskal's algorithm
    Sets ds(graph.n);
    vector<Edge3> mst;

    for (const auto& edge : listEdges) {
        
        // Only add edge to MST if it doesn't create a cycle
        
    }

    // Output MST
    if (mst.size() != graph.n - 1) {
        cout << "No spanning tree found." << endl;
    }
    else {
        cout << "Minimum Spanning Tree:" << endl;
        for (const auto& edge : mst) {
            cout << edge << endl;
        }
    }
}

const int N = 7;

vector<vector<int>> makeGraph() {
    return {
        {0, 28, 0, 0, 0, 10, 0},
        {28, 0, 16, 0, 0, 0, 14},
        {0, 16, 0, 12, 0, 0, 0},
        {0, 0, 12, 0, 22, 0, 18},
        {0, 0, 0, 22, 0, 25, 24},
        {10, 0, 0, 0, 25, 0, 0},
        {0, 14, 0, 18, 24, 0, 0}
    };
}

void showMatrix(const vector<vector<int>>& matrix) {
    cout << "Adjacency matrix:" << endl;
 
}

int main() {
    vector<vector<int>> matrix = makeGraph();
    showMatrix(matrix);
    Graph_MST graph(N);

    // Initialize the graph using adjacency matrix
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                graph.insertEdge3(i, j, matrix[i][j]);
            }
        }
    }

    int select;
    while (true) {
        cout << "\nChoose Command:: 1. Display Adjacency Lists, 2. spanningTree (Kruskal), 3: Quit => ";
        cin >> select;
        switch (select) {
        case 1:
            graph.displayAdjacencyLists();
            break;
        case 2:
            cout << "\nStarting Minimal Spanning Tree process" << endl;
            KruskalMST(graph);
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid input. Please try again." << endl;
        }
    }
}
