#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structura pentru o muchie
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<Edge> edges; // Lista de muchii

    // Structura pentru Disjoint Set Union (DSU)
    struct DSU {
        vector<int> parent, rank;

        DSU(int size) {
            parent.resize(size + 1);
            rank.resize(size + 1, 0);
            for (int i = 1; i <= size; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (x != parent[x]) {
                parent[x] = find(parent[x]); // Compresia drumului
            }
            return parent[x];
        }

        bool unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) return false;

            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
    };

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    // Algoritmul Kruskal
    void kruskal() {
        sort(edges.begin(), edges.end()); // Sortam muchiile dupa greutate
        DSU dsu(n);

        vector<Edge> mst; // Muchiile din arborele minim
        int totalCost = 0;

        for (const Edge& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                mst.push_back(edge);
                totalCost += edge.weight;
            }

            if (mst.size() == n - 1) break; // Daca am gasit toate muchiile necesare
        }

        // Afisare rezultate
        if (mst.size() != n - 1) {
            cout << "Graful nu este conex. Nu se poate construi un arbore minim.\n";
            return;
        }

        cout << "Costul minim al APCM: " << totalCost << "\n";
        cout << "Muchiile din APCM sunt:\n";
        for (const Edge& edge : mst) {
            cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
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

    // Algoritmul Kruskal
    g.kruskal();

    return 0;
}
