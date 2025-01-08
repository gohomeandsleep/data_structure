#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

class Graph {
    vector<list<int>> adjacencyList;
    int n;
    vector<bool> visited;

public:
    Graph(int vertices) : n(vertices), adjacencyList(vertices), visited(vertices, false) {}

    void displayAdjacencyLists() {
       
    }

    void insertEdge(int start, int end) {
       
    }

    void bfs(int startNode) {
        vector<bool> visited(n, false);
        queue<int> queue;

        visited[startNode] = true;
        queue.push(startNode);

        cout << "BFS traversal: ";
        while (!queue.empty()) {
            
        }
        cout << endl;
    }

    void dfs(int startNode) {
        fill(visited.begin(), visited.end(), false);
        cout << "DFS traversal: ";
        nonRecursiveDfs(startNode);
        cout << endl;
    }

    void nonRecursiveDfs(int startNode) {
        stack<int> stack;
        stack.push(startNode);
        visited[startNode] = true;

        while (!stack.empty()) {
           
        }
    }
};

struct InputGraph3 {
    int start, end;

    InputGraph3(int start, int end) : start(start), end(end) {}
};

const int N = 8;

vector<vector<int>> makeGraph() {
    return {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 1, 0}
    };
}

void showMatrix(const vector<vector<int>>& matrix) {

}

int main() {
    vector<vector<int>> matrix = makeGraph();
    showMatrix(matrix);

    Graph g(N);

    while (true) {
        cout << "\nChoose Command: 1: Add edges, 2: Display Adjacency List, 3: BFS, 4: DFS, 5: DFS (Non-Recursive),6: Exit => ";
        int select;
        cin >> select;

        switch (select) {
        case 1: {
            vector<InputGraph3> inputData;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[0].size(); j++) {
                    if (matrix[i][j] == 1) {
                        inputData.emplace_back(i, j);
                    }
                }
            }
            for (const auto& edge : inputData) {
                g.insertEdge(edge.start, edge.end);
            }
            break;
        }

        case 2:
            g.displayAdjacencyLists();
            break;

        case 3: {
            cout << "Enter starting node for BFS: ";
            int startBfsNode;
            cin >> startBfsNode;
            g.bfs(startBfsNode);
            break;
        }

        case 4: {
            cout << "Enter starting node for DFS: ";
            int startDfsNode;
            cin >> startDfsNode;
            g.dfs(startDfsNode);
            break;
        }
        case 5:
            int startDfsNode;
            cin >> startDfsNode;
            std::cout << "Start DFS (non-recursive) from node: " << startDfsNode << "\n";
            g.nonRecursiveDfs(startDfsNode);
            break;
        case 6:
            return 0;

        default:
            cout << "Invalid input. Please re-enter." << endl;
        }
    }
}


