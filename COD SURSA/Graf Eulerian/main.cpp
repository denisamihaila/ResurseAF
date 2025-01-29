#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

    // Functie DFS pentru a verifica daca graful este conex
    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    // Functie pentru a verifica daca graful este conex
    bool isConnected() {
        vector<bool> visited(n + 1, false);

        // Gasim primul nod cu grad > 0
        int start = -1;
        for (int i = 1; i <= n; i++) {
            if (!adj[i].empty()) {
                start = i;
                break;
            }
        }

        // Daca nu exista niciun nod cu grad > 0, graful este considerat conex
        if (start == -1) return true;

        // Pornim DFS din nodul gasit
        dfs(start, visited);

        // Verificam daca toate nodurile cu grad > 0 au fost vizitate
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && !adj[i].empty()) {
                return false;
            }
        }

        return true;
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

    // Determinam daca graful este Eulerian
    void checkEulerian() {
        if (!isConnected()) {
            cout << "Graful nu este conex. Nu este Eulerian.\n";
            return;
        }

        int oddDegree = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() % 2 != 0) {
                oddDegree++;
            }
        }

        if (oddDegree == 0) {
            cout << "Graful este un graf Eulerian (contine un ciclu Eulerian).\n";
        } else if (oddDegree == 2) {
            cout << "Graful contine un drum Eulerian (nu contine un ciclu Eulerian).\n";
        } else {
            cout << "Graful nu este Eulerian.\n";
        }
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

    // Determinam daca graful este Eulerian
    g.checkEulerian();

    return 0;
}
