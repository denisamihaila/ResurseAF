#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<pair<int, int>>> adj; // Liste de adiacenta (nod, greutate)

    // Sortare topologica folosind DFS
    void topologicalSortUtil(int node, vector<bool>& visited, stack<int>& topoStack) {
        visited[node] = true;

        for (auto& neighbor : adj[node]) {
            if (!visited[neighbor.first]) {
                topologicalSortUtil(neighbor.first, visited, topoStack);
            }
        }

        topoStack.push(node);
    }

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie orientata cu greutate
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }

    // Calculeaza drumul de lungime maxima dintr-un nod sursa
    void longestPath(int start) {
        // Pas 1: Sortare topologica
        stack<int> topoStack;
        vector<bool> visited(n + 1, false);

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, topoStack);
            }
        }

        // Pas 2: Initializam distantele
        vector<int> dist(n + 1, INT_MIN);
        dist[start] = 0;

        // Pas 3: Procesam nodurile in ordinea sortarii topologice
        while (!topoStack.empty()) {
            int node = topoStack.top();
            topoStack.pop();

            if (dist[node] != INT_MIN) {
                for (auto& neighbor : adj[node]) {
                    int nextNode = neighbor.first;
                    int weight = neighbor.second;

                    if (dist[node] + weight > dist[nextNode]) {
                        dist[nextNode] = dist[node] + weight;
                    }
                }
            }
        }

        // Afisam distantele maxime
        cout << "Drumurile de lungime maxima din nodul " << start << ":\n";
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MIN) {
                cout << i << ": INF\n"; // Nod inaccesibil
            } else {
                cout << i << ": " << dist[i] << "\n";
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    int start;
    cin >> start;

    // Calculeaza drumurile de lungime maxima din nodul sursa
    g.longestPath(start);

    return 0;
}
