#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class LatinSquareKuhn {
private:
    int n;
    vector<vector<int>> grid;
    vector<vector<int>> graph;
    vector<int> matchCol;
    vector<bool> visited;

public:
    LatinSquareKuhn(int size) {
        n = size;
        grid.resize(n, vector<int>(n, 0));
        graph.resize(n * n);
        matchCol.assign(n * n, -1);
    }

    void citeste_matrice() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }
    }

    void construieste_graf() {
        vector<set<int>> rowPossible(n), colPossible(n);

        // Inițializăm seturile cu toate numerele disponibile pentru fiecare rând și coloană
        for (int i = 0; i < n; i++) {
            for (int num = 1; num <= n; num++) {
                rowPossible[i].insert(num);
                colPossible[i].insert(num);
            }
        }

        // Eliminăm numerele care sunt deja plasate
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 0) {
                    rowPossible[i].erase(grid[i][j]);
                    colPossible[j].erase(grid[i][j]);
                }
            }
        }

        // Construim graful bipartit cu muchii între rânduri și coloane
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) { // Loc liber
                    for (int num : rowPossible[i]) {
                        if (colPossible[j].count(num)) {
                            int rowNode = i * n + (num - 1);
                            int colNode = j * n + (num - 1);
                            graph[rowNode].push_back(colNode);
                            graph[colNode].push_back(rowNode);
                        }
                    }
                }
            }
        }
    }

    bool kuhn(int rowNode) {
        for (int colNode : graph[rowNode]) {
            if (!visited[colNode]) {
                visited[colNode] = true;
                if (matchCol[colNode] == -1 || kuhn(matchCol[colNode])) {
                    matchCol[colNode] = rowNode;
                    return true;
                }
            }
        }
        return false;
    }

    void potrivire_bipartita() {
        for (int i = 0; i < n * n; i++) {
            visited.assign(n * n, false);
            kuhn(i);
        }

        for (int i = 0; i < n * n; i++) {
            if (matchCol[i] != -1) {
                int row = matchCol[i] / n;
                int num = (matchCol[i] % n) + 1;
                int col = (i % n);
                grid[row][col] = num;
            }
        }
    }

    void afiseaza_matrice() {
        for (const auto& row : grid) {
            for (int num : row) {
                cout << num << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int n;
    cin >> n;

    LatinSquareKuhn ls(n);
    ls.citeste_matrice();
    ls.construieste_graf();
    ls.potrivire_bipartita();
    ls.afiseaza_matrice();

    return 0;
}
