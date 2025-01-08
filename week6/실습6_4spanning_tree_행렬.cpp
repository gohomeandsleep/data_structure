#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge4 {
public:
    int src, dest, weight;

    Edge4(int s, int d, int w) : src(s), dest(d), weight(w) {}

    bool operator<(const Edge4& e) const {
        return weight < e.weight;
    }

    friend ostream& operator<<(ostream& os, const Edge4& edge) {
        os << "<" << edge.src << ", " << edge.dest << ", " << edge.weight << ">";
        return os;
    }
};

class Sets2 {
    vector<int> parent;

public:
    Sets2(int n) : parent(n, -1) {}

    int find(int i) {
       
    }

    void unionSets(int x, int y) {
        
    }
};

void KruskalMST(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<Edge4> edges;

    // Extract all edges from adjacency matrix
    

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    // Initialize Disjoint Set for Kruskal's algorithm
    Sets2 ds(n);
    vector<Edge4> mst;

    for (const auto& edge : edges) {
       
        // Only add edge to MST if it doesn't create a cycle
        
    }

    // Output MST
    if (mst.size() != n - 1) {
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

}

int main() {
    vector<vector<int>> matrix = makeGraph();
    showMatrix(matrix);

    int select;
    while (true) {
        cout << "\n명령선택:: 1. Adjacency Matrix 출력, 2. spanningTree (Kruskal), 3: Quit => ";
        cin >> select;
        switch (select) {
        case 1:
            showMatrix(matrix);
            break;
        case 2:
            cout << "\nMinimal Spanning Tree 작업 시작" << endl;
            KruskalMST(matrix);
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            break;
        }
    }
}
