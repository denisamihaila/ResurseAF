#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class BipartiteGraph {
private:
    int n;  // Dimensiunea matricei
    map<int, vector<int>> adj;  // Lista de adiacență
    vector<int> match;  // Vectorul de potriviri
    vector<bool> visited;  // Vector de vizitare pentru DFS

public:
    BipartiteGraph(int size) {
        n = size;
        match.assign(2 * n + 1, -1);  // Inițial, nicio potrivire
    }

    void adauga_muchie(int row, int value) {
        adj[row].push_back(value + n);  // Conectăm rândul `row` la valoarea `value`
    }

    bool kuhn(int node) {
        if (visited[node]) return false;
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (match[neighbor] == -1 || kuhn(match[neighbor])) {
                match[neighbor] = node;
                return true;
            }
        }
        return false;
    }

    void potrivire_maxima(vector<vector<int>>& grid) {
        for (int i = 1; i <= n; i++) {  // Parcurgem fiecare rând
            visited.assign(2 * n + 1, false);
            kuhn(i);
        }

        // Reconstruim pătratul latin pe baza potrivirilor găsite
        for (int value = 1; value <= n; value++) {
            int row = match[value + n];
            if (row != -1) {
                for (int col = 0; col < n; col++) {
                    if (grid[row - 1][col] == 0) {
                        grid[row - 1][col] = value;
                        break;
                    }
                }
            }
        }
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    BipartiteGraph g(n);

    // Citirea pătratului și construirea grafului bipartit
    for (int i = 0; i < n; i++) {
        vector<bool> available(n + 1, true);  // Pentru a ține evidența numerelor disponibile în rând
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) available[grid[i][j]] = false;
        }

        // Conectăm fiecare rând cu valorile lipsă disponibile
        for (int num = 1; num <= n; num++) {
            if (available[num]) g.adauga_muchie(i + 1, num);
        }
    }

    // Aplicăm algoritmul lui Kuhn pentru a găsi completarea validă
    g.potrivire_maxima(grid);

    // Afișăm pătratul completat
    for (const auto& row : grid) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << "\n";
    }

    return 0;
}
