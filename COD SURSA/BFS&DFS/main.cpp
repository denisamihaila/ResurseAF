#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie
    void addEdge(int u, int v, bool isDirected = false) {
        adj[u].push_back(v);
        if (!isDirected) {
            adj[v].push_back(u);
        }
    }

    // BFS
    void bfs(int start) const {
        vector<bool> visited(n + 1, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    // DFS Iterativ
    void dfs(int start) const {
        vector<bool> visited(n + 1, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";

                // Adaugam vecinii in stack
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << "\n";
    }

    // Construieste arborele BFS si il afiseaza
    void bfsTree(int start) const {
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        cout << "Arborele BFS (parinte -> copil):\n";
        for (int i = 1; i <= n; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " -> " << i << "\n";
            }
        }
    }

    // Construieste arborele DFS si il afiseaza
    void dfsTree(int start) const {
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;

                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it]) {
                        parent[*it] = node;
                        s.push(*it);
                    }
                }
            }
        }

        cout << "Arborele DFS (parinte -> copil):\n";
        for (int i = 1; i <= n; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " -> " << i << "\n";
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cin >> start;

    // BFS
    cout << "Parcurgere BFS:\n";
    g.bfs(start);

    // DFS
    cout << "Parcurgere DFS:\n";
    g.dfs(start);

    // Arborele BFS
    g.bfsTree(start);

    // Arborele DFS
    g.dfsTree(start);

    return 0;
}
