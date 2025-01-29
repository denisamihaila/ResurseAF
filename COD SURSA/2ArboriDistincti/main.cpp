#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class Graph {
private:
    int n, m;
    vector<tuple<int, int, int>> edges; // Muchii (cost, u, v)

public:
    // Constructor
    Graph(int nodes, int edgesCount) {
        n = nodes;
        m = edgesCount;
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight) {
        edges.push_back(make_tuple(weight, u, v));
    }

    // Gaseste reprezentantul unui set (Disjoint Set Union - DSU)
    int findSet(int v, vector<int>& parent) {
        if (v == parent[v]) return v;
        return parent[v] = findSet(parent[v], parent);
    }

    // Uneste doua seturi (DSU cu compresie)
    void unionSets(int a, int b, vector<int>& parent, vector<int>& rank) {
        a = findSet(a, parent);
        b = findSet(b, parent);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }

    // Construieste un Arbore de Acoperire Minim (APCM) folosind Kruskal
    vector<tuple<int, int, int>> kruskalAPM() {
        sort(edges.begin(), edges.end()); // Sortam muchiile dupa cost
        vector<int> parent(n + 1), rank(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;

        vector<tuple<int, int, int>> mstEdges;
        for (auto &edge : edges) {
            int weight = get<0>(edge);
            int u = get<1>(edge);
            int v = get<2>(edge);

            if (findSet(u, parent) != findSet(v, parent)) {
                mstEdges.push_back(edge);
                unionSets(u, v, parent, rank);
            }
            if (mstEdges.size() == n - 1) break;
        }

        return mstEdges;
    }

    // Afiseaza doi arbori partiali distincti
    void findTwoDistinctTrees() {
        if (m < n - 1) {
            cout << "Nu\n";
            return;
        }

        vector<tuple<int, int, int>> mstEdges = kruskalAPM();
        if (mstEdges.size() != n - 1) {
            cout << "Nu\n";
            return;
        }

        cout << "Da\n";

        // Afisam primul arbore partial (MST)
        for (auto &edge : mstEdges) {
            int weight = get<0>(edge);
            int u = get<1>(edge);
            int v = get<2>(edge);
            cout << u << " " << v << "\n";
        }
        cout << "\n";

        // Incercam sa gasim un al doilea arbore partial diferit
        for (auto &edge : edges) {
            int weight = get<0>(edge);
            int u = get<1>(edge);
            int v = get<2>(edge);

            // Cautam o muchie care nu e in primul MST
            if (find(mstEdges.begin(), mstEdges.end(), edge) == mstEdges.end()) {
                // Construim un al doilea MST cu aceasta muchie inlocuita
                vector<tuple<int, int, int>> secondTree = mstEdges;
                secondTree.pop_back(); // Scoatem ultima muchie din MST
                secondTree.push_back(edge); // Adaugam noua muchie

                // Afisam al doilea arbore partial
                for (auto &e : secondTree) {
                    int w = get<0>(e);
                    int x = get<1>(e);
                    int y = get<2>(e);
                    cout << x << " " << y << "\n";
                }
                return;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n, m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.findTwoDistinctTrees();
    return 0;
}
