#ifndef TSP_BB_PROBLEMSOLVER_H
#define TSP_BB_PROBLEMSOLVER_H
#include <vector>
#include "DataGenerator.h"

// struktura przechowująca wierzchołek
struct Node {
    int curr, cost, depth;
    std::vector<bool> visit;

    Node() : curr(0), cost(0), depth(0), visit() {}

    Node(int curr, int cost, int depth, const std::vector<bool>& visit)
            : curr(curr), cost(cost), depth(depth), visit(visit) {}
};

// Klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public:
    // funckja do obliczania granicy grafów asymetrycznych
    int calculateBound(int** matrix, std::vector<bool> visited, int size);
    // funckja do obliczania granicy grafów symetrycznych
    int calculateBoundSym(int* symMatrix, std::vector<bool> visited, int size);
    // funckja przekształcająca pozycje ze zwykłej macierzy na index tablicy jednowymiarowej
    int getSymIndex(int i, int j, int n);
    // funckja do przechodzenia grafu w głąb i sprawdzania wagi ścieżki grafu asymetrycznego
    int dfs(int** matrix, int size);
    // funckja do przechodzenia grafu w głąb i sprawdzania wagi ścieżki grafu symetrycznego
    int dfsSym(int* symMatrix, int size);
    // funckja do przechodzenia grafu wszerz i sprawdzania wagi ścieżki grafu asymetrycznego
    int bfs(int** matrix, int size);
    // funckja do przechodzenia grafu wszerz i sprawdzania wagi ścieżki grafu symetrycznego
    int bfsSym(int* symMatrix, int size);
    // funckja do przechodzenia grafu metodą najlepszy pierwszy i sprawdzania wagi ścieżki grafu asymetrycznego
    int bfsZ(int** matrix, int size);
    // funckja do przechodzenia grafu metodą najlepszy pierwszy i sprawdzania wagi ścieżki grafu symetrycznego
    int bfsZSym(int* symMatrix, int size);
};


#endif //TSP_BB_PROBLEMSOLVER_H
