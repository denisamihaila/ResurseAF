#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class GraphWithFlow {
private:
    int n;
    bool isDirected;
    map<int, vector<int>> adj;
    map<pair<int, int>, int> capacity; // Capacitate pe muchie
    map<pair<int, int>, int> flow; // Flux pe muchie

public:
    GraphWithFlow(int nodes = 0, bool directed = false) {
        n = nodes;
        isDirected = directed;
    }

    void adauga_varf(int varf) {
        if (adj.find(varf) == adj.end())
            adj[varf] = {};
    }

    void adauga_muchie(int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Adăugăm și invers pentru rețeaua reziduală
        capacity[{u, v}] += cap;
        flow[{u, v}] = 0; // Inițial, fluxul este 0
        if (!isDirected) {
            capacity[{v, u}] += cap;
            flow[{v, u}] = 0;
        }
    }

    void sterge_muchie(int u, int v) {
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        capacity.erase({u, v});
        flow.erase({u, v});
        if (!isDirected) {
            adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
            capacity.erase({v, u});
            flow.erase({v, u});
        }
    }

    int bfs(int start, int end, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({start, INT_MAX});

        while (!q.empty()) {
            int node = q.front().first;
            int flow_available = q.front().second;
            q.pop();

            for (int neighbor : adj[node]) {
                if (parent[neighbor] == -1 && capacity[{node, neighbor}] - flow[{node, neighbor}] > 0) {
                    parent[neighbor] = node;
                    int new_flow = min(flow_available, capacity[{node, neighbor}] - flow[{node, neighbor}]);
                    if (neighbor == end) return new_flow;
                    q.push({neighbor, new_flow});
                }
            }
        }
        return 0;
    }

    // **Ford-Fulkerson (Edmonds-Karp) – Flux Maxim**
    int maxFlow(int start, int end) {
        int totalFlow = 0;
        vector<int> parent(n + 1);

        while (true) {
            int flow_augment = bfs(start, end, parent);
            if (flow_augment == 0) break;

            totalFlow += flow_augment;

            int current = end;
            while (current != start) {
                int prev = parent[current];
                flow[{prev, current}] += flow_augment;
                flow[{current, prev}] -= flow_augment;
                current = prev;
            }
        }
        return totalFlow;
    }

    // **Verificare flux valid**
    bool verificaFluxValid() {
        for (auto it : flow) {
            if (it.second < 0 || it.second > capacity[it.first])
                return false;
        }
        return true;
    }

    // **Afișare fluxuri pe muchii**
    void afiseaza_fluxuri() {
        cout << "Fluxuri pe muchii:\n";
        for (auto it = capacity.begin(); it != capacity.end(); ++it) {
            int u = it->first.first;
            int v = it->first.second;
            int cap = it->second;
            cout << u << " -> " << v << " : " << flow[{u, v}] << "/" << cap << "\n";
        }
    }

    void afiseaza_graf() {
        cout << "Lista de adiacenta cu capacități:\n";
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            int nod = it->first;
            cout << nod << ": ";
            for (int vecin : it->second) {
                cout << "(" << vecin << ", cap=" << capacity[{nod, vecin}] << ") ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int n, m;
    bool isDirected;
    cout << "Introdu numarul de noduri, muchii si daca este orientat (1 = DA, 0 = NU):\n";
    cin >> n >> m >> isDirected;

    GraphWithFlow g(n, isDirected);
    cout << "Introdu muchiile cu capacitate (u v capacitate):\n";
    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        g.adauga_muchie(u, v, cap);
    }

    g.afiseaza_graf();

    int start, end;
    cout << "Introdu sursa si destinatia pentru flux maxim:\n";
    cin >> start >> end;

    cout << "Fluxul maxim este: " << g.maxFlow(start, end) << "\n";
    g.afiseaza_fluxuri();

    return 0;
}
