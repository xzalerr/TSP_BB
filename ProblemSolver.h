#ifndef TSP_BB_PROBLEMSOLVER_H
#define TSP_BB_PROBLEMSOLVER_H
#include <vector>

struct Node {
    int curr, cost, depth;
    std::vector<bool> visit;
    Node(int curr, int cost, int depth, std::vector<bool> visit) : curr(curr), cost(cost), depth(depth), visit(visit) {}
};

// Klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public:
    // funckja do obliczania granicy
    int calculateBound(std::vector<std::vector<int>>& matrix, std::vector<bool>& visited);
    // funckja do przechodzenia grafu wglab i sprawdzania wagi sciezki
    void dfs(std::vector<std::vector<int>>& matrix, int curr, int depth, int cost, std::vector<bool>& visited);
    void solveDfs(std::vector<std::vector<int>>& matrix);
    int getDfsBest();
    void bfs(std::vector<std::vector<int>>& matrix);
    int getBfsBest();
    void bfsZ(std::vector<std::vector<int>>& matrix);
    int getBfsZBest();
private:
    int dfsCost;
    int bfsCost;
    int bfsZCost;
};


#endif //TSP_BB_PROBLEMSOLVER_H
