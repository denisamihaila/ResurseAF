// drum minim de la un varf de start la toate celelalte
// ponderi pozitive
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<pair<int, int>>> adj; // Liste de adiacenta (nod, cost)

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight, bool isDirected = false) {
        adj[u].push_back({v, weight});
        if (!isDirected) {
            adj[v].push_back({u, weight});
        }
    }

    // Dijkstra
    void dijkstra(int start) const {
        vector<int> dist(n + 1, INT_MAX); // Distantele de la sursa
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start}); // (cost, nod)

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue; // Daca am deja o distanta mai buna, ignor

            for (auto& neighbor : adj[node]) {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (dist[node] + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + edgeWeight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        // Afisare distante
        for (int i = 1; i <= n; i++) {
            cout << (dist[i] == INT_MAX ? -1 : dist[i]) << " ";
        }
        cout << "\n";
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight); // Graf neorientat implicit
        // daca este graf orientat
        // g.addEdge(u, v, weight, true);
    }

    int start;
    cin >> start;

    // Dijkstra
    g.dijkstra(start);

    return 0;
}
