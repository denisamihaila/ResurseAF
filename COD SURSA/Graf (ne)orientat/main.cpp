#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class GraphSimple {
private:
    int n;
    bool isDirected;
    map<int, vector<int>> adj;

public:
    GraphSimple(int nodes = 0, bool directed = false) {
        n = nodes;
        isDirected = directed;
    }

    void adauga_varf(int varf_de_adaugat) {
        if (adj.find(varf_de_adaugat) == adj.end())
            adj[varf_de_adaugat] = {};
    }

    void sterge_varf(int varf_de_sters) {
        adj.erase(varf_de_sters);
        for (auto& it : adj) {
            vector<int>& vecini = it.second;
            vecini.erase(remove(vecini.begin(), vecini.end(), varf_de_sters), vecini.end());
        }
    }

    void adauga_muchie(int u, int v) {
        adj[u].push_back(v);
        if (!isDirected) {
            adj[v].push_back(u);
        }
    }

    void sterge_muchie(int u, int v) {
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        if (!isDirected) {
            adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
        }
    }

    unsigned long numar_varfuri() const {
        return adj.size();
    }

    unsigned long numar_muchii() const {
        unsigned long count = 0;
        for (const auto& it : adj) {
            count += it.second.size();
        }
        return isDirected ? count : count / 2;
    }

    vector<int> obtine_varfuri() const {
        vector<int> nodes;
        for (const auto& it : adj) {
            nodes.push_back(it.first);
        }
        return nodes;
    }

    bool este_muchie(int u, int v) const {
        return find(adj.at(u).begin(), adj.at(u).end(), v) != adj.at(u).end();
    }

    bool este_varf(int varf) const {
        return adj.find(varf) != adj.end();
    }

    void afiseaza_graf() {
        for (const auto& it : adj) {
            cout << it.first << ": ";
            for (int vecin : it.second) {
                cout << vecin << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int n, m;
    bool isDirected;
    cin >> n >> m >> isDirected;

    GraphSimple g(n, isDirected);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.adauga_muchie(u, v);
    }

    g.afiseaza_graf();
    return 0;
}
