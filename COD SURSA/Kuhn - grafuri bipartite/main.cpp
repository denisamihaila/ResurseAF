#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class BipartiteGraph {
private:
    int n, m;  // Număr de noduri în fiecare partiție
    map<int, vector<int>> adj;  // Lista de adiacență
    vector<int> match;  // Vectorul de potriviri
    vector<bool> visited;  // Vector de vizitare pentru DFS

public:
    BipartiteGraph(int leftNodes, int rightNodes) {
        n = leftNodes;
        m = rightNodes;
        match.assign(n + m + 1, -1);  // Inițial, nicio potrivire
    }

    void adauga_muchie(int u, int v) {
        adj[u].push_back(v + n);  // Translatăm dreapta pentru a evita suprapuneri
    }

    void afiseaza_graf() {
        cout << "Lista de adiacenta:\n";
        for (const auto& it : adj) {
            cout << it.first << ": ";
            for (int vecin : it.second) {
                cout << vecin << " ";
            }
            cout << "\n";
        }
    }

    // DFS pentru algoritmul lui Kuhn
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

    // Algoritmul lui Kuhn – Potrivirea maximă
    int potrivire_maxima() {
        int total_matching = 0;
        for (int i = 1; i <= n; i++) {  // Parcurgem nodurile din partea stângă
            visited.assign(n + m + 1, false);  // Resetăm vectorul de vizitare
            if (kuhn(i)) total_matching++;
        }
        return total_matching;
    }

    // Afișează potrivirile găsite
    void afiseaza_potriviri() {
        cout << "Potriviri gasite:\n";
        for (int i = n + 1; i <= n + m; i++) {
            if (match[i] != -1) {
                cout << match[i] << " - " << i - n << "\n";  // Ajustăm indexarea pentru a reflecta nodurile originale
            }
        }
    }
};

int main() {
    int leftNodes, rightNodes, edges;
    cout << "Introdu numarul de noduri in partitia stanga, dreapta si muchii: ";
    cin >> leftNodes >> rightNodes >> edges;

    BipartiteGraph g(leftNodes, rightNodes);

    cout << "Introdu muchiile intre nodurile din cele doua partiții (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.adauga_muchie(u, v);
    }

    cout << "Potrivirea maxima este: " << g.potrivire_maxima() << "\n";
    g.afiseaza_potriviri();

    return 0;
}
