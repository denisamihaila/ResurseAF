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

    // Adauga o muchie neorientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Verifica daca graful este bipartit
    bool isBipartite() {
        vector<int> color(n + 1, -1); // -1 inseamna ca nodul nu este colorat

        for (int start = 1; start <= n; start++) {
            if (color[start] == -1) { // Nodul nu este vizitat
                queue<int> q;
                q.push(start);
                color[start] = 0; // Coloram primul nod cu 0

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : adj[node]) {
                        if (color[neighbor] == -1) {
                            // Coloram vecinul cu culoarea opusa
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            // Daca vecinul are aceeasi culoare, graful nu este bipartit
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    // Afiseaza partitiile grafului, daca este bipartit
    void printPartitions() {
        if (!isBipartite()) {
            cout << "Graful nu este bipartit.\n";
            return;
        }

        vector<int> color(n + 1, -1);
        vector<int> partition1, partition2;

        // Refacem BFS pentru a determina partitiile
        for (int start = 1; start <= n; start++) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0;

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    if (color[node] == 0) {
                        partition1.push_back(node);
                    } else {
                        partition2.push_back(node);
                    }

                    for (int neighbor : adj[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << "Partitia 1:\n";
        for (int node : partition1) {
            cout << node << " ";
        }
        cout << "\nPartitia 2:\n";
        for (int node : partition2) {
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

    // Verifica daca graful este bipartit si afiseaza partitiile
    g.printPartitions();

    return 0;
}
