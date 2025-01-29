#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta
    vector<int> inDegree; // Gradul de intrare pentru fiecare nod

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
        inDegree.resize(n + 1, 0);
    }

    // Adauga o muchie orientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        inDegree[v]++;
    }

    // Sortarea topologica minim lexicografica (BFS - Kahn)
    void topologicalSort() {
        // Sortam listele de adiacență pentru a respecta ordinea minimă lexicografică
        for (int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }

        priority_queue<int, vector<int>, greater<int>> pq;
        vector<int> topoOrder;

        // Adaugam in coada nodurile cu grad de intrare 0
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                pq.push(i);
            }
        }

        // Procesam nodurile
        while (!pq.empty()) {
            int node = pq.top();
            pq.pop();
            topoOrder.push_back(node);

            for (int neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    pq.push(neighbor);
                }
            }
        }

        // Verificam daca graful are cicluri (sortarea este imposibila)
        if (topoOrder.size() < n) {
            cout << "Graful contine cicluri! Sortarea topologica nu este posibila.\n";
            return;
        }

        // Afisam sortarea topologica
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

    // Sortarea topologica minim lexicografica
    g.topologicalSort();

    return 0;
}
