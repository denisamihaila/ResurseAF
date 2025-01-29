#include <iostream>
#include <vector>
using namespace std;

// Clasa pentru reprezentarea unui graf
class Graph {
private:
    int n; // Numarul de noduri
    vector<vector<int>> adj; // Liste de adiacenta

public:
    // Constructor
    Graph(int nodes) {
        n = nodes;
        adj.resize(n + 1);
    }

    // Adauga o muchie
    void addEdge(int u, int v, bool isDirected = false) {
        adj[u].push_back(v);
        if (!isDirected) {
            adj[v].push_back(u);
        }
    }

    // Getter pentru numarul de noduri
    int getNodes() const {
        return n;
    }

    // Getter pentru lista de adiacenta
    vector<int> getNeighbors(int node) {
        return adj[node];
    }
};

int main() {
    int n, m;
    cin >> n >> m; // Citeste numarul de noduri si muchii

    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v; // Citeste muchia
        g.addEdge(u, v); // Adauga muchia in graf (neorientat implicit)
    }

    return 0;
}











/**
2ArboriDistincti – Determina daca un graf neorientat are cel putin doi arbori partiali distincti si ii afiseaza.

Bellman-Ford – Determina drumul minim de la un nod sursa la toate celelalte in grafuri orientate/neorientate cu ponderi (poate avea ponderi negative si detecteaza cicluri negative).

BFS & DFS – Parcurgeri clasice pentru grafuri orientate/neorientate folosite la determinarea componentelor conexe, ciclurilor si traseelor.

Dijkstra – Calculeaza drumul minim de la un nod sursa la toate celelalte pentru grafuri orientate/neorientate cu ponderi pozitive.

Distanta de editare – Determina numarul minim de operatii necesare pentru a transforma un sir in altul (util in bioinformatica si corectare automata).

Drum de lungime maxima – Calculeaza cel mai lung drum intr-un graf orientat aciclic (DAG), util in programare dinamica pe grafuri.

Edmonds-Karp – Algoritm bazat pe BFS pentru determinarea fluxului maxim intr-un graf cu capacitate, aplicabil la probleme de transport.

Floyd-Warshall – Determina toate distantele minime intre toate perechile de noduri dintr-un graf cu ponderi pozitive si negative (dar fara cicluri negative).

Ford-Fulkerson – Algoritm de flux maxim aplicabil pe grafuri orientate/neorientate, bazat pe cautarea drumurilor de augmentare.

Graf (ne)orientat – Implementare de baza a unui graf orientat sau neorientat, cu operatii fundamentale asupra nodurilor si muchiilor.

Graf bipartit – Determina daca un graf neorientat este bipartit (se poate colora cu doua culori fara conflicte), aplicabil in alocarea de resurse si planificare.

Graf cu costuri – Graf orientat/neorientat cu ponderi pe muchii, folosit in probleme de drum minim si arbore partial minim.

Graf cu flux – Graf orientat cu capacitati, utilizat in probleme de transport si retele de flux.

Graf Eulerian – Determina daca un graf contine un ciclu Eulerian sau un drum Eulerian (parcurgere a tuturor muchiilor o singura data).

Graf Hamiltonian – Determina daca un graf contine un ciclu Hamiltonian sau un drum Hamiltonian (vizitarea fiecarui nod o singura data).

Kahn – Algoritm de sortare topologica bazat pe BFS, utilizat in ordonarea activitatilor dependente (ex: planificare proiecte).

Kosaraju – Algoritm pentru determinarea componentelor tare conexe din grafuri orientate, aplicabil in analiza dependintelor.

Kruskal – Determina Arborele Partial de Cost Minim (APCM) folosind structura de reuniune-disjunctie (Union-Find).

Prim – Algoritm de construire a unui arbore partial de cost minim, potrivit pentru grafuri dens conectate.

Roy-Floyd – Varianta algoritmului Floyd-Warshall utilizata pentru calcularea distantelor minime intr-un graf orientat/neorientat.

SortTopDFS – Algoritm de sortare topologica bazat pe DFS, utilizat in ordonarea activitatilor dependente si analizarea dependintelor.

Structura de baza – Implementare generala pentru grafuri, utilizata ca suport pentru algoritmi fundamentali.

Tarjan – Algoritm eficient pentru determinarea componentelor tare conexe din grafuri orientate.
**/


/** Citire si scriere in fisier
#include<fstream>
ifstream f("date.in");
ofstream g("date.out");
f>> ;
g<< ;
f.close();
g.close();
**/
