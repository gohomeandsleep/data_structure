#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Pair {
    int vertex;
    int weight;

    Pair(int v, int d) : vertex(v), weight(d) {}
};

class Graph {
private:
    vector<vector<Pair>> HeadNodes; // Adjacency Lists
    vector<int> count; // Incoming degree count
    vector<int> ee;  // earliest event time
    vector<int> le; // latest event time
    int n;  // 전체 노드수

public:
    Graph(int vertices = 0) : n(vertices) {
        HeadNodes.resize(n);
        count.resize(n, 0);
        ee.resize(n, 0);
        le.resize(n, 0);
    }

    void showArray(const std::vector<int>& arr) const; // Declaration

    void Setup8();
    void Setup9();
    void EarlyActivity();
    void EarlyActivity_display();
    void LateActivity();
    void LateActivity_display();
    void display_early_late_criticalActivity();
    void TopologicalOrder();
    void addEdge(int start, int end, int weight);
    void printAdjacencyLists() const;
    Graph* inverseGraph() const;
};

void Graph::addEdge(int start, int end, int weight) {
    if (start < 0 || end >= n) {
        cout << "노드 번호가 out of bounds." << endl;
        return;
    }

}

void Graph::printAdjacencyLists() const {
    cout << "Adjacency Lists:" << endl;
    for (int i = 0; i < n; i++) {
   
    }
}

Graph* Graph::inverseGraph() const {
    auto* inverseGraph = new Graph(n);//auto는 자동 타입 추론 > 생성된 Graph 객체를 가리키는 포인터 타입
    for (int i = 0; i < n; i++) {
  
    }
    return inverseGraph;
}

void Graph::TopologicalOrder() {
    vector<int> indegreeCount = count;
    queue<int> queZeroNodes;

    for (int i = 0; i < n; i++) {

    }

    while (!queZeroNodes.empty()) {
   
    }
    cout << endl;
}

void Graph::EarlyActivity() {
    // early activity time 계산
    vector<int> indegreeCount = count;//각 노드의 indegree를 저장
    queue<int> queZeroNodes;//노드의 indegree가 0인 노드들을 큐에 유지

    for (int i = 0; i < n; i++) {

    }

    ee.assign(n, 0);

    while (!queZeroNodes.empty()) {
  
    }
}

void Graph::LateActivity() {
    EarlyActivity();
    int maxTime = *max_element(ee.begin(), ee.end());
    // max_element()는 <algorithm> 헤더에 정의된 표준 라이브러리 함수로, **컨테이너 내에서 가장 큰 값을 가리키는 반복자(iterator)**를 반환

    le.assign(n, maxTime);

    Graph* invGraph = this->inverseGraph();
    vector<int> outdegreeCount = invGraph->count;
    queue<int> queZeroNodes;

    for (int i = 0; i < n; i++) {

    }

    while (!queZeroNodes.empty()) {

    }

    delete invGraph;
}

void Graph::display_early_late_criticalActivity() {
    //ai = <k,l>
    //e(i) = ee[k]
    //l[i] = le[l]-duration of ai

    EarlyActivity();
    LateActivity();

    cout << endl;
    for (int k = 0; k < n; k++) {

    }
}

void Graph::Setup8() {
    addEdge(0, 3, 5);
    addEdge(0, 2, 4);
    addEdge(0, 1, 6);
    addEdge(1, 4, 1);
    addEdge(2, 4, 1);
    addEdge(3, 5, 2);
    addEdge(4, 7, 7);
    addEdge(4, 6, 9);
    addEdge(5, 7, 4);
    addEdge(6, 8, 2);
    addEdge(7, 8, 4);
}
void Graph::Setup9() {
    addEdge(0, 2, 6);
    addEdge(0, 1, 5);
    addEdge(1, 3, 3);
    addEdge(2, 3, 6);
    addEdge(2, 4, 3);
    addEdge(3, 5, 4);
    addEdge(3, 6, 4);
    addEdge(3, 4, 3);
    addEdge(4, 6, 1);
    addEdge(4, 7, 4);
    addEdge(5, 8, 7);
    addEdge(5, 9, 4);
    addEdge(6, 8, 5);
    addEdge(7, 8, 2);
    addEdge(8, 9, 2);
}

void Graph::LateActivity_display() {
    for (int i = 0; i < n; i++) {
        ee[i] = 0;
    }

    EarlyActivity();

    Graph* invGraph = this->inverseGraph();
    const auto& inversedHeadNodes = invGraph->HeadNodes; // Use vector<list<Pair>> directly
    vector<int> inversedCount = invGraph->count;         // Use vector for counts

    cout << endl;
    invGraph->printAdjacencyLists(); // Print adjacency lists

    // Get and set max value in ee
    int max = -1;
 
    // Create a queue for vertices with no predecessors
    queue<int> q;
    for (int i = 0; i < n; i++) {

    }

    cout << endl << "Display le (late event occurrence time) " << endl;
    cout << "initial   ";
    showArray(le); // Display initial `le` array

    while (!q.empty()) {
        
    }

    for (int i = 0; i < n; i++) {
        if (inversedCount[i] > 0) {
            cout << "The network has a cycle" << endl;
            delete invGraph;
            return;
        }
    }

    showArray(le); // Final display of `le`
    delete invGraph;
}

void displayQueue(const std::queue<int>& q) {
    std::queue<int> temp = q; // Create a copy to safely iterate
    std::cout << "Queue: ";
    while (!temp.empty()) {

    }
    std::cout << std::endl;
}

// The n vertices of a network are listed in topological order
void Graph::EarlyActivity_display() {
    // Copy count array to countArr vector
    std::vector<int> countArr(count.begin(), count.end());
    std::vector<int> ee(n, 0); // Initialize ee with zeros
    std::queue<int> queue;     // Use std::queue for processing vertices

    // Enqueue vertices with no predecessors
    for (int i = 0; i < n; i++) {

    }

    std::cout << "Display ee (early event occurrence time)" << std::endl;
    std::cout << "initial   ";
    showArray(ee); // Display initial ee
    displayQueue(queue); // Display initial queue

    // Process vertices in topological order using a queue
    while (!queue.empty()) {
   
    }

    // Final display of ee
    showArray(ee);
}
void Graph::showArray(const std::vector<int>& arr) const {

}

int main() {
    Graph* g = nullptr;
    int select = 0, n, start, end, weight;

    cout << "1: 연습문제 그래프 사용, 2: 교재 그래프 사용: ";
    cin >> select;
    if (select == 1) {
        cout << "그래프 노드 수: 10개인 그래프: ";
        g = new Graph(9);
        g->Setup8();
    }
    else if (select == 2) {
        cout << "그래프 노드 수: 9개인 그래프: ";
        g = new Graph(9);
        g->Setup8();
    }

    while (select != 8) {
        cout << "\n2: Print Adjacency Lists, 3: Inverse Graph, 4: Early Activity,"
            << " 5: Late Activity, 6: Critical Activity, 7: Topological Order, 8: Quit => ";
        cin >> select;

        switch (select) {
        case 1:
            break;
        case 2:
            g->printAdjacencyLists();
            break;
        case 3: {
            Graph* invGraph = g->inverseGraph();
            invGraph->printAdjacencyLists();
            delete invGraph;
            break;
        }
        case 4:
            g->EarlyActivity_display();
            break;
        case 5:
            g->LateActivity_display();
            break;
        case 6:
            g->display_early_late_criticalActivity();
            break;
        case 7:
            g->TopologicalOrder();
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid input. Try again." << endl;
        }
    }

    delete g;
    return 0;
}
