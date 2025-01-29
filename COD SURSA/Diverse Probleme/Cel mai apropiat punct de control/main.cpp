#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<pair<int, int>>> adj; // Liste de adiacenta (nod, cost)
    bool isDirected; // Flag pentru orientare

public:
    // Constructor
    Graph(int nodes, bool directed) {
        n = nodes;
        isDirected = directed;
        adj.resize(n + 1);
    }

    // Adauga o muchie
    void addEdge(int u, int v, int weight = 1) {
        adj[u].push_back({v, weight});
        if (!isDirected) { // Doar pentru graful neorientat
            adj[v].push_back({u, weight});
        }
    }

    // BFS (Pentru grafuri neorientate)
    pair<int, vector<int>> bfs(int start, const vector<int>& controlPoints) {
        vector<int> dist(n + 1, INT_MAX);
        vector<int> parent(n + 1, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto neighbor : adj[node]) {
                int nextNode = neighbor.first;
                if (dist[nextNode] == INT_MAX) {
                    dist[nextNode] = dist[node] + 1;
                    parent[nextNode] = node;
                    q.push(nextNode);
                }
            }
        }

        // Gasim cel mai apropiat punct de control
        int minDist = INT_MAX;
        int closestControl = -1;
        for (int cp : controlPoints) {
            if (dist[cp] < minDist) {
                minDist = dist[cp];
                closestControl = cp;
            }
        }

        // Reconstruim drumul
        vector<int> path;
        if (closestControl != -1) {
            int node = closestControl;
            while (node != -1) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
        }

        return {closestControl, path};
    }

    // Dijkstra (Pentru grafuri orientate cu ponderi)
    pair<int, vector<int>> dijkstra(int start, const vector<int>& controlPoints) {
        vector<int> dist(n + 1, INT_MAX);
        vector<int> parent(n + 1, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int node = pq.top().second;
            int cost = pq.top().first;
            pq.pop();

            if (cost > dist[node]) continue;

            for (auto neighbor : adj[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[node] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + weight;
                    parent[nextNode] = node;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        // Gasim cel mai apropiat punct de control
        int minDist = INT_MAX;
        int closestControl = -1;
        for (int cp : controlPoints) {
            if (dist[cp] < minDist) {
                minDist = dist[cp];
                closestControl = cp;
            }
        }

        // Reconstruim drumul
        vector<int> path;
        if (closestControl != -1) {
            int node = closestControl;
            while (node != -1) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
        }

        return {closestControl, path};
    }
};

int main() {
    int n, m;
    bool isDirected; // Se citeste daca graful este orientat sau nu
    cin >> n >> m >> isDirected;

    Graph g(n, isDirected);
    for (int i = 0; i < m; i++) {
        int u, v, weight = 1;
        cin >> u >> v;
        if (isDirected) cin >> weight; // Citim si costul pentru grafurile orientate
        g.addEdge(u, v, weight);
    }

    int k;
    cin >> k;
    vector<int> controlPoints(k);
    for (int i = 0; i < k; i++) {
        cin >> controlPoints[i];
    }

    int start;
    cin >> start;

    pair<int, vector<int>> result;
    if (isDirected) {
        result = g.dijkstra(start, controlPoints); // Folosim Dijkstra pentru graf orientat
    } else {
        result = g.bfs(start, controlPoints); // Folosim BFS pentru graf neorientat
    }

    if (result.first == -1) {
        cout << "Nu exista punct de control accesibil\n";
    } else {
        cout << "Cel mai apropiat punct de control este: " << result.first << "\n";
        cout << "Drumul minim: ";
        for (int node : result.second) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}
