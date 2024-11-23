#ifndef TSP_BB_PROBLEMSOLVER_H
#define TSP_BB_PROBLEMSOLVER_H
#include "Vector.h"
#include "DataGenerator.h"

struct Node {
    int curr, cost, depth;
    bool* visit;

    Node() : curr(0), cost(0), depth(0), visit(nullptr) {}

    Node(int curr, int cost, int depth, bool* visit, int size)
        : curr(curr), cost(cost), depth(depth) {
        this->visit = new bool[size];
        for(int i = 0; i < size; i++) {
            this->visit[i] = visit[i];
        }
    }
};

// Klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public:
    // funckja do obliczania granicy
    int calculateBound(int** matrix, bool* visited, int size);
    // funckja do przechodzenia grafu wglab i sprawdzania wagi sciezki
    int dfs(int** matrix, int size);
    int bfs(int** matrix, int size);
    int bfsZ(int** matrix, int size);
};


#endif //TSP_BB_PROBLEMSOLVER_H
