#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <utility>
using namespace std;

const int MAX_WEIGHT = 9999999;
const int nmax = 100;
// Graph class with adjacency list
class Graph {
private:
    int n; // number of nodes
    int length[nmax][nmax]; //connection matrix
    int a[nmax][nmax];
    vector<list<pair<int, int>>> HeadNodes; // adjacency list (node, weight)
    vector<int> dist;
    vector<bool> s;
    vector<int> newdist;

public:
    Graph(int nodeSize) : n(nodeSize), HeadNodes(nodeSize), dist(nodeSize), s(nodeSize), newdist(nodeSize) {

    }

    void insertEdge(int start, int end, int weight);
    void showAdjacencyList();
    void ShortestPath(const int v);
    void ShortestPath_display(const int v);
    void BellmanFord(const int v);
    void BellmanFord2(const int v);
    void AllLengths();
    int choose();
    void show_dist_array(int startNode);
    void Graph::showGraphMatrix(int n);
    bool isNonNegativeEdgeCost();

    // Helper functions for output
    void displaySet();
    void Graph::showAdjacencyMatrix();
};

void Graph::insertEdge(int start, int end, int weight) {
    if (start >= n || end >= n || start < 0 || end < 0) {
        cout << "The input node is out of bound, the largest node is " << (n - 1) << endl;
        return;
    }

}

void Graph::showAdjacencyList() {
    for (int i = 0; i < n; i++) {

    }
}

void Graph::show_dist_array(int startNode) {
    for (int i = 0; i < n; i++) {

    }
    cout << endl;
}

bool Graph::isNonNegativeEdgeCost() {
    for (int i = 0; i < n; i++) {

    }
    return true;
}

void Graph::ShortestPath(const int v) {
    //dist[j], 0<=j<=n, is set to the length of the shortest path from vertex v to vertex j
    // in a digraph G with n vertices and edge lengths given by length[i][j]
    for (int i = 0; i < n; i++) {// initialize
        s[i] = false;
        dist[i] = length[v][i];
    }

    dist[v] = 0;
    s[v] = true;

    for (int i = 0; i < n - 2; i++) { // determine n-1 paths from vertex v
        int u = choose();  // choose returns a value u such that:

    } //end of for (i=0;...)
}

void Graph::ShortestPath_display(const int v) {
    for (int i = 0; i < n; i++) {// initialize
        s[i] = false;
        dist[i] = length[v][i];
    }
    dist[v] = 0;
    s[v] = true;

    for (int i = 0; i < n - 1; i++) {

    }
    displaySet();
    show_dist_array(v);
}

int Graph::choose() {
    int minDist = MAX_WEIGHT;
    int index = -1;
    for (int i = 0; i < n; i++) {

    }
    return index;
}

void Graph::displaySet() {
    cout << "[";
    for (int i = 0; i < n; i++) {

    }
    cout << "] ";
}


void Graph::BellmanFord(const int v) {
    //single source all destination shortest paths with negative edge lengths
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i];//initialize dist[]
    //
    cout << endl;
    int k = 0;
    for (k = 1; k <= n - 1; k++) {
   
    }
    //cout << "k = " << k << ", ";
    //show_dist_array(n);
}

void Graph::BellmanFord2(const int v)
// Single source all destination shortest paths with negative edge lengths
{
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i]; // initialize dist
    for (int k = 2; k <= n - 1; k++) {

    }
}
void Graph::showGraphMatrix(int n) {
    //cout << endl;
    for (int i = 0; i < n; i++) {

    }
}
void Graph::AllLengths()
// length[n][n] is the adjacency matrix of a graph with n vertices.
// a[i][j] is the length of the shortest path between i and j
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = length[i][j];   // copy length into a

    int k = 0;
    for (; k < n; k++) {  // for a path with highest vertex index k

    }
    cout << "\n A[" << k - 1 << "]" << endl;
    showGraphMatrix(n);
}

void Graph::showAdjacencyMatrix() {
    for (int i = 0; i < n; i++) {
    
    }
}





vector<vector<int>> makeGraph1() {
    return {
        {0, 6, 5, 7, 0, 0, 0},
        {6, 0, 2, 0, 1, 0, 0},
        {5, 2, 0, 2, 1, 0, 0},
        {7, 0, 2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 3},
        {0, 0, 0, 1, 0, 0, 8},
        {0, 0, 0, 0, 3, 8, 0}
    };
}

vector<vector<int>> makeGraph2() {
    return {
        {0, 300, 1000, 0, 0, 0, 0, 1700},
        {300, 0, 800, 0, 0, 0, 0, 0},
        {1000, 800, 0, 1200, 0, 0, 0, 0},
        {0, 0, 0, 1200, 1500, 1000, 0, 0},
        {0, 0, 0, 1500, 0, 250, 0, 0},
        {0, 0, 0, 1000, 250, 0, 900, 1400},
        {0, 0, 0, 0, 0, 900, 0, 1000},
        {1700, 0, 0, 0, 0, 1400, 1000, 0}
    };
}
void showMatrix(vector<vector<int>> matrix) {
    for (auto row : matrix) {

    }
}
int main() {
    int num;
    int select;
    Graph* g = nullptr;
    int start, end, weight;
    cout << "1: Graph with Negative Weights, 2: 도시간 거리 그래프\n";
    cin >> select;

    if (select == 1) {
        auto matrix = makeGraph1();
        showMatrix(matrix);
        g = new Graph(7);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != 0) {
                    g->insertEdge(i, j, matrix[i][j]);
                }
            }
        }
    }
    else if (select == 2) {
        auto matrix = makeGraph2();
        showMatrix(matrix);
        g = new Graph(8);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != 0) {
                    g->insertEdge(i, j, matrix[i][j]);
                }
            }
        }
    }
    else {
        cout << "Invalid input. Exiting." << endl;
        return 0;
    }
    while (select != '0')
    {
        cout << "\nSelect command 1: Edge 추가, 2: AdjacencyLists, 3: singleSource/all destinations(non-negative edge cost)"
            << "4:  single source/all destinations(negative edge costs), 5. All-pairs shortest paths, 6. Quit => ";
        cin >> select;
        switch (select) {
        case 1:
            cout << "edge 추가: " << endl;
            cout << "start node: ";
            cin >> start;
            cout << "end  node: ";
            cin >> end;
            cout << "weight: ";
            cin >> weight;

            g->insertEdge(start, end, weight);
            break;
        case 2:
            //display
            g->showAdjacencyMatrix();
            break;
        case 3:
            cout << "\nsingle source/all destinations: non-negative edge costs: " << endl;
            if (!g->isNonNegativeEdgeCost()) {
                cout << "Negative edge cost exists!!" << endl;
                cout << "Please re-build the graph with non-negative edge costs." << endl;
                break;
            }

            cout << "\n ----------> Input start node: ";
            cin >> start;

            g->ShortestPath_display(start);
            break;
        case 4:
            cout << "\nsingle source/all destinations: negative edge costs: " << endl;
            cout << "\n ----------> Input start node: ";
            cin >> start;

            g->BellmanFord(start);
            break;
        case 5:
            cout << "\nAll-pairs shortest paths:" << endl;
            g->AllLengths();
            break;
        case 6:
            exit(0);
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
            break;
        }
    }

    cin >> num;
    delete g;
    return 0;
}
