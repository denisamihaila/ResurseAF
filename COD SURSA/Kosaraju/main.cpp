#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

    // Functie utilitara pentru DFS in primul pas
    void dfs1(int node, vector<bool>& visited, stack<int>& finishOrder) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, visited, finishOrder);
            }
        }

        finishOrder.push(node); // Adaugam nodul pe stack cand "se termina"
    }

    // Functie utilitara pentru DFS in graful transpus
    void dfs2(int node, vector<bool>& visited, vector<int>& component, const vector<vector<int>>& transposed) {
        visited[node] = true;
        component.push_back(node);

        for (int neighbor : transposed[node]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, visited, component, transposed);
            }
        }
    }

    // Functie pentru a construi graful transpus
    vector<vector<int>> transposeGraph() {
        vector<vector<int>> transposed(n + 1);

        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                transposed[v].push_back(u); // Inversam muchia
            }
        }

        return transposed;
    }

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie orientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Algoritmul Kosaraju pentru a gasi SCC
    void kosaraju() {
        vector<bool> visited(n + 1, false);
        stack<int> finishOrder;

        // Pasul 1: Primul DFS pentru a determina ordinea de terminare
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs1(i, visited, finishOrder);
            }
        }

        // Pasul 2: Inversam graful
        vector<vector<int>> transposed = transposeGraph();

        // Pasul 3: Al doilea DFS pe graful inversat
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> stronglyConnectedComponents;

        while (!finishOrder.empty()) {
            int node = finishOrder.top();
            finishOrder.pop();

            if (!visited[node]) {
                vector<int> component;
                dfs2(node, visited, component, transposed);
                stronglyConnectedComponents.push_back(component);
            }
        }

        // Afisam componentele tare conexe
        cout << "Componentele tare conexe sunt:\n";
        for (const auto& component : stronglyConnectedComponents) {
            for (int node : component) {
                cout << node << " ";
            }
            cout << "\n";
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

    // Algoritmul Kosaraju
    g.kosaraju();

    return 0;
}
