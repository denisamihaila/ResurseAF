#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
using namespace std;

class GraphWithCosts {
private:
    int n;
    map<int, vector<pair<int, int>>> adj;

public:
    GraphWithCosts(int nodes) {
        n = nodes;
    }

    void adauga_muchie(int u, int v, int cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }

    // Algoritmul Dijkstra pentru drumuri minime și părinți multipli
    vector<int> dijkstra(int start, map<int, vector<int>>& parent) {
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first, node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto& neighbor : adj[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[node] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + weight;
                    pq.push({dist[nextNode], nextNode});
                    parent[nextNode] = {node}; // Salvăm părintele unic
                } else if (dist[node] + weight == dist[nextNode]) {
                    parent[nextNode].push_back(node); // Salvăm toate căile minime
                }
            }
        }

        return dist;
    }

    // Verifică dacă nodul `k` se află pe un drum minim între `i` și `j`
    bool este_critic(int i, int j, int k) {
        if (i == k || j == k) return true; // Dacă `k` este chiar `i` sau `j`, atunci e pe traseu

        map<int, vector<int>> parent;
        vector<int> dist = dijkstra(i, parent);

        if (dist[j] == INT_MAX) return false; // Dacă `j` nu este accesibil de la `i`, returnăm 0

        // Verificăm dacă `k` este pe drumul minim refăcând toate traseele minime de la `j` la `i`
        queue<int> q;
        q.push(j);
        map<int, bool> onPath;
        onPath[j] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int p : parent[node]) {
                if (!onPath[p]) {
                    onPath[p] = true;
                    q.push(p);
                }
            }
        }

        return onPath[k]; // Dacă `k` este în lista de părinți, returnăm `true`
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // Optimizare pentru citire rapidă

    int n, m;
    cin >> n >> m;

    GraphWithCosts g(n);
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        g.adauga_muchie(u, v, cost);
    }

    int q;
    cin >> q;
    string output = ""; // String pentru output compact

    while (q--) {
        int i, j, k;
        cin >> i >> j >> k;
        output += (g.este_critic(i, j, k) ? '1' : '0');
    }

    // Afișăm tot output-ul odată, fără newline
    cout << output << "\n";

    return 0;
}
