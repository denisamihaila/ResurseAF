// arbore partial de cost minim in graf ponderat neorientat, incepand dintr-un varf anume
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adjMatrix; // Matrice de adiacenta

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adjMatrix.resize(n + 1, vector<int>(n + 1, 0));
    }

    // Adauga o muchie (graf neorientat)
    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    // Functie utilitara pentru a gasi nodul cu costul minim
    int minKey(vector<int>& key, vector<bool>& inMST) const {
        int min = INT_MAX, min_index;

        for (int v = 1; v <= n; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

    // Algoritmul lui Prim
    void prim() const {
        vector<int> parent(n + 1, -1); // Stocam arborele minim
        vector<int> key(n + 1, INT_MAX); // Costurile minime pentru fiecare nod
        vector<bool> inMST(n + 1, false); // Noduri incluse in MST

        // Pornim din nodul 1
        key[1] = 0;
        parent[1] = -1;

        for (int count = 1; count <= n - 1; count++) {
            // Alege nodul cu costul minim care nu este in MST
            int u = minKey(key, inMST);
            inMST[u] = true;

            // Actualizam costurile pentru vecinii nodului ales
            for (int v = 1; v <= n; v++) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        // Afisam costul total al arborelui minim
        int totalCost = 0;
        for (int i = 2; i <= n; i++) {
            totalCost += adjMatrix[i][parent[i]];
        }
        cout << "Costul minim al APM: " << totalCost << "\n";

        // Afisam muchiile din APM
        for (int i = 2; i <= n; i++) {
            cout << parent[i] << " " << i << "\n";
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

    // Algoritmul lui Prim
    g.prim();

    return 0;
}
