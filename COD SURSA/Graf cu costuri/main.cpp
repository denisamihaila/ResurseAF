#include <iostream>
#include <vector>
#include <map>
#include <queue>
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

    // Dijkstra – Drum minim de la un nod sursa
    void dijkstra(int start) {
        map<int, int> dist;
        for (auto& it : adj) dist[it.first] = 1e9;
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first, node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto& neighbor : adj[node]) {
                int v = neighbor.first, cost = neighbor.second;
                if (dist[node] + cost < dist[v]) {
                    dist[v] = dist[node] + cost;
                    pq.push({dist[v], v});
                }
            }
        }

        for (auto& it : dist) cout << it.first << ": " << it.second << "\n";
    }

    // Bellman-Ford – Drum minim si detectare ciclu negativ
    void bellmanFord(int start) {
        map<int, int> dist;
        for (auto& it : adj) dist[it.first] = 1e9;
        dist[start] = 0;

        for (int i = 1; i < n; i++) {
            for (auto& edge : costs) {
                int u = edge.first.first, v = edge.first.second, cost = edge.second;
                if (dist[u] != 1e9 && dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                }
            }
        }

        for (auto& edge : costs) {
            int u = edge.first.first, v = edge.first.second, cost = edge.second;
            if (dist[u] != 1e9 && dist[u] + cost < dist[v]) {
                cout << "Ciclu negativ detectat!\n";
                return;
            }
        }

        for (auto& it : dist) cout << it.first << ": " << it.second << "\n";
    }

    // Floyd-Warshall – Drum minim intre toate perechile de noduri
    void floydWarshall() {
        map<int, map<int, int>> dist;
        for (auto& it : adj) {
            for (auto& neighbor : it.second) {
                dist[it.first][neighbor.first] = neighbor.second;
            }
            dist[it.first][it.first] = 0;
        }

        for (auto& k : adj) {
            for (auto& i : adj) {
                for (auto& j : adj) {
                    if (dist[i.first][k.first] + dist[k.first][j.first] < dist[i.first][j.first]) {
                        dist[i.first][j.first] = dist[i.first][k.first] + dist[k.first][j.first];
                    }
                }
            }
        }

        for (auto& it : dist) {
            for (auto& d : it.second) {
                cout << "De la " << it.first << " la " << d.first << ": " << d.second << "\n";
            }
        }
    }

    // Kruskal – Arbore minim de acoperire
    void kruskal() {
        vector<pair<int, pair<int, int>>> edges;
        for (auto& edge : costs) {
            edges.push_back({edge.second, {edge.first.first, edge.first.second}});
        }

        sort(edges.begin(), edges.end());
        map<int, int> parent;
        for (auto& it : adj) parent[it.first] = it.first;

        function<int(int)> find = [&](int v) {
            return parent[v] == v ? v : parent[v] = find(parent[v]);
        };

        int totalCost = 0;
        for (auto& edge : edges) {
            int u = edge.second.first, v = edge.second.second, cost = edge.first;
            if (find(u) != find(v)) {
                parent[find(u)] = find(v);
                totalCost += cost;
                cout << u << " - " << v << " (" << cost << ")\n";
            }
        }
        cout << "Cost total APM: " << totalCost << "\n";
    }

    // Prim – Arbore minim de acoperire
    void prim(int start) {
        map<int, int> key;
        map<int, bool> inMST;
        map<int, int> parent;
        for (auto& it : adj) key[it.first] = 1e9, inMST[it.first] = false, parent[it.first] = -1;

        key[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first, cost = neighbor.second;
                if (!inMST[v] && cost < key[v]) {
                    key[v] = cost;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Arborele minim de acoperire:\n";
        for (auto& it : parent) {
            if (it.second != -1) cout << it.second << " - " << it.first << " (" << key[it.first] << ")\n";
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
