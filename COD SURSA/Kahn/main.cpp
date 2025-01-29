#include <iostream>
#include <vector>
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

    // Adauga o muchie orientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Algoritmul Kahn pentru sortare topologica
    void kahn() {
        vector<int> inDegree(n + 1, 0); // Gradul de intrare al fiecarui nod
        vector<int> topoOrder; // Sortarea topologica
        queue<int> q; // Coada pentru nodurile cu in-degree 0

        // Calculam gradul de intrare pentru fiecare nod
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }

        // Adaugam in coada toate nodurile cu in-degree 0
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Procesam nodurile din coada
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);

            // Reducem gradul de intrare pentru vecini
            for (int neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Verificam daca graful contine cicluri
        if (topoOrder.size() != n) {
            cout << "Graful nu este aciclic. Nu se poate realiza sortarea topologica.\n";
            return;
        }

        // Afisam sortarea topologica
        cout << "Sortarea topologica este:\n";
        for (int node : topoOrder) {
            cout << node << " ";
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

    // Algoritmul Kahn
    g.kahn();

    return 0;
}
