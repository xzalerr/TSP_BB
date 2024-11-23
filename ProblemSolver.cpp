#include "ProblemSolver.h"
#include <queue>
#include <stack>

int ProblemSolver::calculateBound(int** matrix, bool* visited, int size) {
    int bound = 0;
    int n = size;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int minIn = INT_MAX, minOut = INT_MAX;
            for (int j = 0; j < n; j++) {
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

int ProblemSolver::dfs(int** matrix, int size) {
    int n = size;
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
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfs(int** matrix, int size) {
    int n = size;
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
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZ(int** matrix, int size) {
    int n = size;
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
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit, size);
                node.visit[i] = false;
            }
        }
    }
    return best;
}