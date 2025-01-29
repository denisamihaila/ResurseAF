// drumul minim de la un nod de start la toate celelalte
// detecteaza cicluri negative, deci sunt permise ponderi negative
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> edges; // Lista de muchii (u, v, cost)
    bool isDirected; // Flag pentru graf orientat/neorientat

public:
    // Constructor
    Graph(int nodes, bool directed) {
        n = nodes;
        isDirected = directed;
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
        if (!isDirected) {
            edges.push_back({v, u, weight}); // Adaugam inversa doar daca graful este neorientat
        }
    }

    // Algoritmul Bellman-Ford
    void bellmanFord(int start) const {
        vector<int> dist(n + 1, 1e8);
        dist[start] = 0;

        // Relaxam toate muchiile de n ori pentru detectarea ciclurilor negative
        for (int i = 0; i < n; i++) {
            for (auto& edge : edges) {
                int u = edge[0], v = edge[1], weight = edge[2];

                if (dist[u] != 1e8 && dist[u] + weight < dist[v]) {
                    // Daca suntem in ultima relaxare, inseamna ca exista ciclu negativ
                    if (i == n - 1) {
                        cout << "Ciclu negativ detectat\n";
                        return;
                    }
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Afisam distantele
        for (int i = 1; i <= n; i++) {
            cout << (dist[i] == 1e8 ? -1 : dist[i]) << " ";
        }
        cout << "\n";
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    bool isDirected = 1; // Daca graful este orientat (1) sau neorientat (0)

    Graph g(n, isDirected);
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    int start;
    cin >> start;

    // Bellman-Ford
    g.bellmanFord(start);

    return 0;
}
