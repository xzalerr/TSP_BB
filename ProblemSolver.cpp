#include "ProblemSolver.h"
#include <queue>

int ProblemSolver::calculateBound(std::vector<std::vector<int>> &matrix, std::vector<bool> &visited) {
    int bound = 0;
    int n = matrix.size();
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            int min = INT_MAX;
            for(int j = 0; j < n; j++) {
                if(i != j) min = std::min(matrix[i][j], min);
            }
            bound += min;
        }
    }
    return bound;
}

void ProblemSolver::dfs(std::vector<std::vector<int>> &matrix, int curr, int depth, int cost, std::vector<bool> &visited) {
    int n = matrix.size();
    if(depth == n) {
        if(cost + matrix[curr][0] < dfsCost) dfsCost = cost + matrix[curr][0];
        return;
    }
    int bound = calculateBound(matrix, visited);
    if(bound >= dfsCost) return;
    for(int i = 0; i < n; i++) {
        if(!visited[i] && matrix[curr][i] != -1) {
            visited[i] = true;
            if(cost + bound < dfsCost) {
                dfs(matrix, i, depth + 1, cost + matrix[curr][i], visited);
            }
            visited[i] = false;
        }
    }
}

void ProblemSolver::solveDfs(std::vector<std::vector<int>> &matrix) {
    dfsCost = INT_MAX;
    std::vector<bool> visited(matrix.size(), false);
    visited[0] = true;
    dfs(matrix, 0, 1, 0, visited);
}

int ProblemSolver::getDfsBest() {
    return dfsCost;
}

void ProblemSolver::bfs(std::vector<std::vector<int>> &matrix) {
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
    bfsCost = best;
}

int ProblemSolver::getBfsBest() {
    return bfsCost;
}

void ProblemSolver::bfsZ(std::vector<std::vector<int>> &matrix) {
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
    bfsZCost = best;
}

int ProblemSolver::getBfsZBest() {
    return bfsZCost;
}