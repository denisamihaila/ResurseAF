#include <iostream>
#include <vector>
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

    // DFS pentru a gasi un drum de augmentare
    int dfs(int node, int end, vector<int>& parent, vector<bool>& visited, int flow) {
        if (node == end) {
            return flow; // Am ajuns la destinatie, returnam fluxul minim pe drum
        }
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor] && capacity[node][neighbor] > 0) {
                int new_flow = min(flow, capacity[node][neighbor]);
                parent[neighbor] = node;

                int result = dfs(neighbor, end, parent, visited, new_flow);
                if (result > 0) {
                    return result;
                }
            }
        }

        return 0; // Nu s-a gasit drum
    }

    // Ford-Fulkerson pentru flux maxim
    int fordFulkerson(int start, int end) {
        int maxFlow = 0;
        vector<int> parent(n + 1);
        vector<bool> visited(n + 1);

        while (true) {
            fill(parent.begin(), parent.end(), -1);
            fill(visited.begin(), visited.end(), false);

            int flow = dfs(start, end, parent, visited, INT_MAX);
            if (flow == 0) break; // Nu mai exista drumuri de augmentare

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

    // Ford-Fulkerson
    cout << g.fordFulkerson(start, end);

    return 0;
}
