#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int vertices;                // liczba wierzchołków
    vector<vector<int>> list;

public:
    Graph(int v) {
        vertices = v;
        list.resize(v);
    }

    ~Graph(){}

    void add(int x, int y) {
        list[x].push_back(y);
    }

    bool secondDFS(int node, vector<char>& visited) {
        visited[node] = 'b';

        for (int next : list[node]) {
            if (visited[next] == 'w') {
                if (secondDFS(next, visited)) {
                    return true;    // petla wykryta
                }
            } else if (visited[next] == 'b') {
                return true;        // petla wykryta
            }
        }

        visited[node] = 'g';
        return false;
    }

    void sort() {
        for(int i = 0; i < vertices; i++) {
            std::sort(list[i].begin(), list[i].end());
        }
    }

    bool dfs(int start) {
        vector<char> visited(vertices, 'w');   // w - nieodwiedzony, g - odwiedzony, b - w trakcie odwiedzania

        if (secondDFS(start, visited)) {
            return true;             // petla zostala znaleziona
        }
        return false;                // petla nie zostala znaleziona (w main przechodzi do bfs)
    }

    vector<int> bfs(int start) {
        sort();
        queue<int> q;
        vector<bool> visited(vertices, false);
        vector<int> previous(vertices, -1);
        vector<int> previous2(vertices, -1);
        vector<int> path = {};
        int node;
        bool found = false;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            node = q.front();
            q.pop();

            if (list[node].empty()) {
                found = true;
                break;
            }

            for (int next : list[node]) {
                for (int nextNext : list[next]) {
                    if (!visited[nextNext]) {
                        q.push(nextNext);
                        visited[nextNext] = true;
                        previous[nextNext] = next;
                        previous2[nextNext] = node;
                    }
                }
            }
        }

        if(!found) {
            return {};
        }

        path.push_back(node);
        for (int i = node; i != start; i = previous2[i]) {
            path.push_back(previous[i]);
            path.push_back(previous2[i]);
        }
        std::reverse(path.begin(), path.end());

        return path;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    cin >> t;   // ilosc testow

    while (t--) {
        int n, m, s;
        cin >> n >> m >> s;     // ilosc wierzcholkow, polaczen, start

        Graph graph(n);

        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            graph.add(x, y);
        }

        vector<int> result = graph.bfs(s);
        bool isEmpty = result.empty();

        if(isEmpty && graph.dfs(s)) {
            cout << "PETLA\n";
            continue;
        }

        if(isEmpty) {
            cout << "NIE\n";
            continue;
        }

        cout << "TAK\n";
        for (int index : result) {
            cout << index << " ";
        }
        cout << "\n";
    }
    return 0;
}