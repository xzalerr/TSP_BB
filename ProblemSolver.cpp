#include "ProblemSolver.h"
#include <queue>
#include <stack>

int ProblemSolver::calculateBound(int** matrix, bool* visited, int size) {
    int bound = 0;
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            int minIn = INT_MAX, minOut = INT_MAX;
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    minIn = std::min(minIn, matrix[j][i]);
                    minOut = std::min(minOut, matrix[i][j]);
                }
            }
            bound += (minIn + minOut) / 2;
        }
    }

    return bound;
}

int ProblemSolver::calculateBoundSym(int *symMatrix, bool *visited, int size) {
    int bound = 0;
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            int min = INT_MAX;
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    min = std::min(min, symMatrix[getSymIndex(i, j, size)]);
                }
            }
            bound += min;
        }
    }
    return bound;
}

int ProblemSolver::getSymIndex(int i, int j, int n) {
    if (i > j) std::swap(i, j);
    return i * (2 * n - i - 1) / 2 + (j - i - 1);
}

int ProblemSolver::dfs(int** matrix, int size) {
    std::stack<Node> frontier;
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::dfsSym(int *symMatrix, int size) {
    std::stack<Node> frontier;
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfs(int** matrix, int size) {
    std::queue<Node> frontier;
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.front();
        frontier.pop();
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsSym(int *symMatrix, int size) {
    std::queue<Node> frontier;
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.front();
        frontier.pop();
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZ(int** matrix, int size) {
    auto compBfsZ = [] (Node n1, Node n2) {
        return n1.cost > n2.cost;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compBfsZ)> frontier(compBfsZ);
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZSym(int *symMatrix, int size) {
    auto compBfsZ = [] (Node n1, Node n2) {
        return n1.cost > n2.cost;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compBfsZ)> frontier(compBfsZ);
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;
    Node first(0, 0, 1, visited, size);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}