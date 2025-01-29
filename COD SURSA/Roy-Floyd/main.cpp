#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> dist; // Matricea distantelor

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        dist.resize(n + 1, vector<int>(n + 1, INT_MAX));

        // Distanta de la un nod la el insusi este 0
        for (int i = 1; i <= n; i++) {
            dist[i][i] = 0;
        }
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight) {
        dist[u][v] = weight;
    }

    // Algoritmul Roy-Floyd
    void royFloyd() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }

    // Afiseaza matricea distantelor
    void printDistances() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
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
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    // Algoritmul Roy-Floyd
    g.royFloyd();

    // Afisare distante
    cout << "Matricea distantelor minime:\n";
    g.printDistances();

    return 0;
}
