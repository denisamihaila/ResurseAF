// fluxul maxim
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> capacity; // Matricea de capacitati
    vector<vector<int>> adj; // Liste de adiacenta

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        capacity.resize(n + 1, vector<int>(n + 1, 0));
        adj.resize(n + 1);
    }

    // Adauga o muchie orientata cu capacitate
    void addEdge(int u, int v, int cap) {
        capacity[u][v] += cap; // Capacitatea initiala
        adj[u].push_back(v);
        adj[v].push_back(u); // Adaugam muchia inversa in reteaua reziduala
    }

    // BFS pentru a gasi un drum de augmentare
    int bfs(int start, int end, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({start, INT_MAX}); // (nod curent, fluxul minim pe drum)

        while (!q.empty()) {
            int node = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int neighbor : adj[node]) {
                if (parent[neighbor] == -1 && capacity[node][neighbor] > 0) {
                    // Daca nodul nu a fost vizitat si exista capacitate disponibila
                    parent[neighbor] = node;
                    int new_flow = min(flow, capacity[node][neighbor]);
                    if (neighbor == end) {
                        return new_flow; // Daca ajungem la nodul destinatie
                    }
                    q.push({neighbor, new_flow});
                }
            }
        }

        return 0; // Nu exista drum de augmentare
    }

    // Edmonds-Karp pentru flux maxim
    int edmondsKarp(int start, int end) {
        int maxFlow = 0;
        vector<int> parent(n + 1);

        while (int flow = bfs(start, end, parent)) {
            maxFlow += flow;

            // Actualizam capacitatile in reteaua reziduala
            int current = end;
            while (current != start) {
                int prev = parent[current];
                capacity[prev][current] -= flow;
                capacity[current][prev] += flow;
                current = prev;
            }
        }

        return maxFlow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        g.addEdge(u, v, cap);
    }

    int start, end;
    cin >> start >> end;

    // Edmonds-Karp
    cout << g.edmondsKarp(start, end);

    return 0;
}
