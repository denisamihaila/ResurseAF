#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

    // Backtracking pentru a verifica ciclul Hamiltonian
    bool hamiltonianUtil(int node, vector<bool>& visited, vector<int>& path, int count) {
        visited[node] = true;
        path.push_back(node);

        // Daca am vizitat toate nodurile, verificam daca putem inchide ciclul
        if (count == n) {
            // Daca exista o muchie inapoi catre nodul de start, avem un ciclu
            if (find(adj[node].begin(), adj[node].end(), path[0]) != adj[node].end()) {
                path.push_back(path[0]);
                return true;
            } else {
                visited[node] = false;
                path.pop_back();
                return false;
            }
        }

        // Incercam sa extindem drumul
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (hamiltonianUtil(neighbor, visited, path, count + 1)) {
                    return true;
                }
            }
        }

        // Daca nu gasim o solutie, facem backtrack
        visited[node] = false;
        path.pop_back();
        return false;
    }

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie neorientata
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Verificam daca graful contine un ciclu Hamiltonian
    void hamiltonianCycle() {
        vector<bool> visited(n + 1, false);
        vector<int> path;

        for (int start = 1; start <= n; start++) {
            if (hamiltonianUtil(start, visited, path, 1)) {
                cout << "Ciclu Hamiltonian gasit:\n";
                for (int node : path) {
                    cout << node << " ";
                }
                cout << "\n";
                return;
            }
        }

        cout << "Nu exista ciclu Hamiltonian in graf.\n";
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Verificam ciclul Hamiltonian
    g.hamiltonianCycle();

    return 0;
}
