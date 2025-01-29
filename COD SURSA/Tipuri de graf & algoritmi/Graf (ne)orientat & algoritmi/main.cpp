#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
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

    void adauga_muchie(int u, int v) {
        adj[u].push_back(v);
        if (!isDirected) adj[v].push_back(u);
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

    // BFS
    void bfs(int start) {
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    // DFS
    void dfs(int start) {
        vector<bool> visited(n + 1, false);
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << "\n";
    }

    // Dijkstra cu cost implicit 1
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

            for (int neighbor : adj[node]) {
                if (dist[node] + 1 < dist[neighbor]) {
                    dist[neighbor] = dist[node] + 1;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }

        for (auto& it : dist) cout << it.first << ": " << it.second << "\n";
    }

    // Verificare bipartit
    bool esteBipartit() {
        map<int, int> color;
        queue<int> q;

        for (auto& it : adj) {
            int start = it.first;
            if (color.find(start) == color.end()) {
                color[start] = 0;
                q.push(start);

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : adj[node]) {
                        if (color.find(neighbor) == color.end()) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // Verificare Eulerian
    void verificaEulerian() {
        int odd = 0;
        for (auto& it : adj) {
            if (it.second.size() % 2 != 0) odd++;
        }

        if (odd == 0) cout << "Graful are un ciclu Eulerian.\n";
        else if (odd == 2) cout << "Graful are un drum Eulerian.\n";
        else cout << "Graful nu este Eulerian.\n";
    }

    // Verificare Hamiltonian (heuristic)
    void verificaHamiltonian() {
        if (adj.size() < 3) {
            cout << "Graful nu este Hamiltonian (prea putine noduri).\n";
            return;
        }
        cout << "Heuristic: Graful *poate* fi Hamiltonian daca fiecare nod are grad >= n/2.\n";
    }

    // Kosaraju - Componente tari conexe
    void kosaraju() {
    if (!isDirected) return;

    stack<int> s;
    map<int, bool> visited;

    function<void(int)> dfs1 = [&](int node) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) dfs1(neighbor);
        }
        s.push(node);
    };

    // First pass (on original graph)
    for (auto& it : adj) {
        if (!visited[it.first]) {
            dfs1(it.first);
        }
    }

    // Build reverse adjacency
    map<int, vector<int>> revAdj;
    for (auto& it : adj) {
        for (int v : it.second) {
            revAdj[v].push_back(it.first);
        }
    }

    // Reset visited (OLD: fill(visited.begin(), visited.end(), false);)
    for (auto &kv : visited) {
        kv.second = false;
    }

    // Second pass (on reversed graph)
    function<void(int)> dfs2 = [&](int node) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : revAdj[node]) {
            if (!visited[neighbor]) dfs2(neighbor);
        }
    };

    // Pop nodes in order from stack
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited[node]) {
            dfs2(node);
            cout << "\n";
        }
    }
}


    // Sortare topologica Kahn
    void sortareTopologicaKahn() {
        if (!isDirected) return;

        map<int, int> inDegree;
        for (auto& it : adj) inDegree[it.first] = 0;
        for (auto& it : adj) for (int v : it.second) inDegree[v]++;

        queue<int> q;
        for (auto& it : inDegree) if (it.second == 0) q.push(it.first);

        vector<int> sorted;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            sorted.push_back(node);

            for (int neighbor : adj[node]) if (--inDegree[neighbor] == 0) q.push(neighbor);
        }

        for (int node : sorted) cout << node << " ";
        cout << "\n";
    }

    // Sortare topologica DFS
    void sortTopDFS() {
        if (!isDirected) return;

        stack<int> s;
        map<int, bool> visited;

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int neighbor : adj[node]) if (!visited[neighbor]) dfs(neighbor);
            s.push(node);
        };

        for (auto& it : adj) if (!visited[it.first]) dfs(it.first);

        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << "\n";
    }

    // Tarjan - Articulații și componente tari conexe
    void tarjan() {
        map<int, int> disc, low;
        map<int, bool> visited;
        stack<int> s;
        vector<vector<int>> scc;
        int time = 0;

        function<void(int)> dfs = [&](int node) {
            disc[node] = low[node] = ++time;
            s.push(node);
            visited[node] = true;

            for (int neighbor : adj[node]) {
                if (!disc[neighbor]) {
                    dfs(neighbor);
                    low[node] = min(low[node], low[neighbor]);
                } else if (visited[neighbor]) {
                    low[node] = min(low[node], disc[neighbor]);
                }
            }

            if (low[node] == disc[node]) {
                vector<int> component;
                while (s.top() != node) {
                    component.push_back(s.top());
                    visited[s.top()] = false;
                    s.pop();
                }
                component.push_back(node);
                visited[node] = false;
                s.pop();
                scc.push_back(component);
            }
        };

        for (auto& it : adj) if (!disc[it.first]) dfs(it.first);
        for (auto& c : scc) {
            for (int v : c) cout << v << " ";
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

    cout << "Afisare graf:\n";
    g.afiseaza_graf();
    cout << "\n";

    // BFS & DFS
    cout << "BFS pornind din nodul 1:\n";
    g.bfs(1);
    cout << "DFS pornind din nodul 1:\n";
    g.dfs(1);
    cout << "\n";

    // Dijkstra (cost implicit 1)
    cout << "Dijkstra (distante minime de la 1, cost implicit 1):\n";
    g.dijkstra(1);
    cout << "\n";

    // Verificare bipartit
    cout << "Graful este bipartit? " << (g.esteBipartit() ? "Da" : "Nu") << "\n\n";

    // Verificare Eulerian
    cout << "Verificare daca graful este Eulerian:\n";
    g.verificaEulerian();
    cout << "\n";

    // Verificare Hamiltonian
    cout << "Verificare daca graful este Hamiltonian:\n";
    g.verificaHamiltonian();
    cout << "\n";

    // Sortare topologica Kahn (doar pentru grafuri orientate)
    if (isDirected) {
        cout << "Sortare topologica folosind algoritmul lui Kahn:\n";
        g.sortareTopologicaKahn();
        cout << "\n";
    }

    // Sortare topologica DFS (doar pentru grafuri orientate)
    if (isDirected) {
        cout << "Sortare topologica folosind DFS:\n";
        g.sortTopDFS();
        cout << "\n";
    }

    // Kosaraju - Componente tari conexe (doar pentru grafuri orientate)
    if (isDirected) {
        cout << "Componente tari conexe (Kosaraju):\n";
        g.kosaraju();
        cout << "\n";
    }

    // Tarjan - Componente tari conexe și puncte critice/articulații
    cout << "Componente tari conexe si puncte critice (Tarjan):\n";
    g.tarjan();
    cout << "\n";

    // Stergere muchie
    cout << "Stergere muchie (1 -> 3):\n";
    g.sterge_muchie(1, 3);
    g.afiseaza_graf();
    cout << "\n";

    return 0;
}
