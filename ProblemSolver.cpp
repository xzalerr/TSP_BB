#include "ProblemSolver.h"
#include <queue>
#include <stack>

int ProblemSolver::calculateBound(std::vector<std::vector<int>> &matrix, std::vector<bool> &visited) {
    int bound = 0;
    int n = matrix.size();
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

int ProblemSolver::dfs(std::vector<std::vector<int>> &matrix) {
    int n = matrix.size();
    std::stack<Node> frontier;
    std::vector<bool> visited(n, false);
    visited[0] = true;
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfs(std::vector<std::vector<int>> &matrix) {
    int n = matrix.size();
    std::queue<Node> frontier;
    std::vector<bool> visited(n, false);
    visited[0] = true;
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.front();
        frontier.pop();
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZ(std::vector<std::vector<int>> &matrix) {
    int n = matrix.size();
    auto compBfsZ = [] (Node n1, Node n2) {
        return n1.cost > n2.cost;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compBfsZ)> frontier(compBfsZ);
    std::vector<bool> visited(n, false);
    visited[0] = true;
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    while(!frontier.empty()) {
        Node node = frontier.top();
        frontier.pop();
        if(node.depth == n) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        int bound = calculateBound(matrix, node.visit);
        if(bound + node.cost >= best) continue;
        for(int i = 0; i < n; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}