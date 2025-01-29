#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta
    vector<int> disc; // Timpurile de descoperire in DFS
    vector<int> low; // Timpurile minime de intoarcere
    vector<bool> visited; // Marcare noduri vizitate
    set<pair<int, int>> criticalEdges; // Muchii critice
    vector<int> articulationPoints; // Noduri critice
    int timer;

    // DFS pentru Tarjan
    void tarjanDFS(int node, int parent) {
        visited[node] = true;
        disc[node] = low[node] = timer++;
        int children = 0; // Numarul de copii in DFS pentru nodul curent

        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue; // Ignoram muchia de intoarcere

            if (!visited[neighbor]) {
                children++;
                tarjanDFS(neighbor, node);

                // Actualizam low pentru nodul curent
                low[node] = min(low[node], low[neighbor]);

                // Detectam muchii critice
                if (low[neighbor] > disc[node]) {
                    criticalEdges.insert({min(node, neighbor), max(node, neighbor)});
                }

                // Detectam noduri critice
                if (parent != -1 && low[neighbor] >= disc[node]) {
                    articulationPoints.push_back(node);
                }
            } else {
                // Actualizam low daca gasim un ciclu inapoi
                low[node] = min(low[node], disc[neighbor]);
            }
        }

        // Radacina DFS este un punct de articulatie daca are cel putin doi copii
        if (parent == -1 && children > 1) {
            articulationPoints.push_back(node);
        }
    }

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
        disc.resize(n + 1, -1);
        low.resize(n + 1, -1);
        visited.resize(n + 1, false);
        timer = 0;
    }

    // Adauga o muchie neorientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Algoritmul Tarjan
    void tarjan() {
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                tarjanDFS(i, -1);
            }
        }

        // Afisam muchiile critice
        cout << "Muchiile critice sunt:\n";
        for (const auto& edge : criticalEdges) {
            cout << edge.first << " " << edge.second << "\n";
        }

        // Afisam nodurile critice
        cout << "Nodurile critice sunt:\n";
        for (int node : articulationPoints) {
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

    // Algoritmul Tarjan
    g.tarjan();

    return 0;
}
