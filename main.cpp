#include <iostream>
#include "DataGenerator.h"
#include "ProblemSolver.h"
#include <iostream>
#include <chrono>

int main() {
    DataGenerator dg;
    ProblemSolver ps;

    // Opcjonalne ładowanie danych z pliku
    // dg.loadData("/Users/rafalzalecki/CLionProjects/TravellingSalesmanProblemBruteForce/matrix_6x6.atsp");
    dg.generateDataAsymmetric(10);

    // Mierzenie czasu dla DFS
    auto start = std::chrono::high_resolution_clock::now();
    ps.solveDfs(dg.matrix);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Minimalna wartosc sciezki znaleziona przez dfs: " << ps.getDfsBest() << "\n";
    std::cout << "Czas wykonania DFS: " << duration << " ms\n";

    // Mierzenie czasu dla BFS
    start = std::chrono::high_resolution_clock::now();
    ps.bfs(dg.matrix);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Minimalna wartosc sciezki znaleziona przez bfs: " << ps.getBfsBest() << "\n";
    std::cout << "Czas wykonania BFS: " << duration << " ms\n";

    // Mierzenie czasu dla Best-First Search (bfsZ)
    start = std::chrono::high_resolution_clock::now();
    ps.bfsZ(dg.matrix);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Minimalna wartosc sciezki znaleziona przez bfsZ: " << ps.getBfsZBest() << "\n";
    std::cout << "Czas wykonania BFSz: " << duration << " ms\n";

    return 0;
}