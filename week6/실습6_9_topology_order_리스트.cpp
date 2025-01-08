#include <iostream>
#include <vector>
#include <list>
#include <queue> // queue 포함

using namespace std;

// 함수: 인접 행렬 반환
vector<vector<int>> makeGraph() {
    return {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
}

class Graph {
private:
    int n;                       // Number of vertices
    vector<list<int>> HeadNodes;       // Adjacency list
    vector<int> count;           // Count of incoming edges (in-degree)

public:
    void Setup1();
    void Setup2();
    void printAdjacencyLists() const;
    Graph(int vertices) : n(vertices) {
        HeadNodes.resize(vertices);
        count.resize(vertices, 0);
    }

    // 행렬을 사용해 그래프 구성
    void makeGraph(const vector<vector<int>>& matrix) {
        for (int i = 0; i < matrix.size(); i++) {
   
        }
    }

    void addEdge(int u, int v) {

    }

    void TopologicalOrder() {
        queue<int> q;            // Queue to store vertices with 0 in-degree
        for (int i = 0; i < n; i++) {
    
        }

        vector<int> result;      // Store the topological order

        while (!q.empty()) {

        }

        // Check if all vertices are processed
        if (result.size() != n) {
            cout << "Network has a cycle" << endl;
            return; // Graph contains a cycle
        }

        // Output the topological order
        cout << "Topological Order: ";
        for (int vertex : result) {
            cout << vertex << " ";
        }
        cout << endl;
    }
};
void Graph::Setup1() {
    addEdge(0, 3);
    addEdge(0, 2);
    addEdge(0, 1);
    addEdge(1, 4);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(4, 7);
    addEdge(4, 6);
    addEdge(5, 7);
    addEdge(6, 8);
    addEdge(7, 8);
}
void Graph::Setup2() {
    addEdge(0, 2);
    addEdge(0, 1);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(3, 6);
    addEdge(3, 4);
    addEdge(4, 6);
    addEdge(4, 7);
    addEdge(5, 8);
    addEdge(5, 9);
    addEdge(6, 8);
    addEdge(7, 8);
    addEdge(8, 9);
}
void Graph::printAdjacencyLists() const {
    cout << "Adjacency Lists:" << endl;
    for (int i = 0; i < n; i++) {
 
    }
}
int main() {
    int num = 0, select = 0;
    // 그래프 생성 및 행렬로부터 그래프 빌드
    vector<vector<int>> matrix = makeGraph();
    int vertices = matrix.size();
    Graph g(vertices);
    Graph* graph = nullptr;
    Graph* graph2 = nullptr;
    while (select != 8) {
        cout << "\n1: 행렬 그래프, 2: 인접그래프1, 3. 인접그래프2:: ";
        cin >> select;

        switch (select) {
        case 1:
            g.makeGraph(matrix);
            g.printAdjacencyLists();
            // 위상 정렬 수행
            g.TopologicalOrder();
            break;

        case 2:
            graph = new Graph(9);
            graph->Setup1();
            graph->printAdjacencyLists();
            // 위상 정렬 수행
            graph->TopologicalOrder();
            break;
        case 3: {
            graph2 = new Graph(10);
            graph2->Setup2();
            graph2->printAdjacencyLists();
            // 위상 정렬 수행
            graph2->TopologicalOrder();
            break;
        default:
            return 0;
        }
        }
    }
    return 0;
}
