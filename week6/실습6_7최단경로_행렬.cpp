#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph5 {
private:
    static const int NMAX = 10;
    static const int MAX_WEIGHT = INT_MAX;

    int length[NMAX][NMAX];
    int dist[NMAX];
    bool s[NMAX];
    int n;

public:
    Graph5(int nodeSize) : n(nodeSize) {
        for (int i = 0; i < NMAX; i++) {
            for (int j = 0; j < NMAX; j++) {
                length[i][j] = MAX_WEIGHT;  // Initialize all edges to "infinite" distance (no path)
            }
        }
    }

    void insertEdge(int start, int end, int weight) {

    }

    void displayConnectionMatrix() {
        for (int i = 0; i < n; i++) {
    
        }
    }

    bool isNonNegativeEdgeCost() {
        for (int i = 0; i < n; i++) {
    
        }
        return true;
    }

    void shortestPath(int startNode) {
        fill(s, s + n, false);
        for (int i = 0; i < n; i++) {
            dist[i] = length[startNode][i];
        }
        s[startNode] = true;
        dist[startNode] = 0;


        printDistances(startNode);
    }

private:
    int choose() {
        int minDist = MAX_WEIGHT;
        int index = -1;

    }

    void printDistances(int startNode) {

    }
};

void showMatrix(const vector<vector<int>>& matrix) {

}

vector<vector<int>> makeGraph1() {
    return {
        {0, 6, 5, 7, 0, 0, 0},
        {6, 0, -2, 0, -1, 0, 0},
        {5, -2, 0, -2, 1, 0, 0},
        {7, 0, -2, 0, 0, -1, 0},
        {0, -1, 1, 0, 0, 0, 3},
        {0, 0, 0, -1, 0, 0, 8},
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

int main() {
    int select;
    Graph5* g = nullptr;

    cout << "1: Graph with Negative Weights, 2: City Distance Graph\n";
    cin >> select;

    if (select == 1) {
        auto matrix = makeGraph1();
        showMatrix(matrix);
        g = new Graph5(7);
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
        g = new Graph5(8);
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

    while (true) {
        cout << "\nCommands: 1: Display Matrix, 2: Dijkstra (non-negative), 3: Quit => ";
        cin >> select;
        if (select == 3) break;

        switch (select) {
        case 1:
            g->displayConnectionMatrix();
            break;
        case 2:
            if (g->isNonNegativeEdgeCost()) {
                cout << "Start node: ";
                int startNode;
                cin >> startNode;
                g->shortestPath(startNode);
            }
            else {
                cout << "Graph contains negative edges. Use the Bellman-Ford algorithm instead." << endl;
            }
            break;
        default:
            cout << "Invalid input. Try again." << endl;
        }
    }

    delete g;
    return 0;
}
