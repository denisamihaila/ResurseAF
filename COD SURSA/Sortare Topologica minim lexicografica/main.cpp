#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

    // Functie recursiva pentru DFS
    void dfs(int node, vector<bool>& visited, stack<int>& topoStack) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, topoStack);
            }
        }

        topoStack.push(node); // Adaugam nodul pe stack cand este complet explorat
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

    // Sortarea topologica folosind DFS
    void topologicalSort() {
        vector<bool> visited(n + 1, false);
        stack<int> topoStack;

        // Apelam DFS pentru fiecare nod nevizitat
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, visited, topoStack);
            }
        }

        // Afisam sortarea topologica
        cout << "Sortarea topologica este:\n";
        while (!topoStack.empty()) {
            cout << topoStack.top() << " ";
            topoStack.pop();
        }
        cout << "\n";
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

    // Sortarea topologica
    g.topologicalSort();

    return 0;
}
