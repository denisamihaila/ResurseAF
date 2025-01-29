#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class GraphWithCosts {
private:
    int n;
    bool isDirected;
    map<int, vector<pair<int, int>>> adj;
    map<pair<int, int>, int> costs;

public:
    GraphWithCosts(int nodes = 0, bool directed = false) {
        n = nodes;
        isDirected = directed;
    }

    void adauga_varf(int varf) {
        if (adj.find(varf) == adj.end())
            adj[varf] = {};
    }

    void adauga_muchie(int u, int v, int cost) {
        adj[u].push_back({v, cost});
        costs[{u, v}] = cost;
        if (!isDirected) {
            adj[v].push_back({u, cost});
            costs[{v, u}] = cost;
        }
    }

    void sterge_muchie(int u, int v) {
        adj[u].erase(remove_if(adj[u].begin(), adj[u].end(),
                               [v](pair<int, int> p) { return p.first == v; }), adj[u].end());
        costs.erase({u, v});
        if (!isDirected) {
            adj[v].erase(remove_if(adj[v].begin(), adj[v].end(),
                                   [u](pair<int, int> p) { return p.first == u; }), adj[v].end());
            costs.erase({v, u});
        }
    }

    int obtine_cost(int u, int v) const {
        return costs.count({u, v}) ? costs.at({u, v}) : -1;
    }

    void afiseaza_graf() {
        for (const auto& it : adj) {
            int nod = it.first;
            cout << nod << ": ";
            for (const auto& vecin : it.second) {
                cout << "(" << vecin.first << ", cost: " << costs[{nod, vecin.first}] << ") ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int n, m;
    bool isDirected;
    cin >> n >> m >> isDirected;

    GraphWithCosts g(n, isDirected);
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        g.adauga_muchie(u, v, cost);
    }

    g.afiseaza_graf();
    return 0;
}
