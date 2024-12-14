#include "ProblemSolver.h"
#include <queue>
#include <stack>

int ProblemSolver::calculateBound(int** matrix, std::vector<bool> visited, int size) {
    /* początkowo granica wynosi 0, następnie zwiększyamy granicę o wartość średnią
     * z wchodzących i wychodzących najmniejszych krawędzi dla każdego
     * nieodwiedzonego wierzchołka */
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

int ProblemSolver::calculateBoundSym(int *symMatrix, std::vector<bool> visited, int size) {
    /* początkowo granica wynosi 0, następnie zwiększyamy granicę o wartość
     * najmniejszych krawędzi wychodzących z każdego nieodwiedzonego wierzchołka */
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
    // przekształcane są współrzędne macierzy [i][j] na pojedynczy index do jednowymiarowej tablicy
    if (i > j) std::swap(i, j);
    return i * (2 * n - i - 1) / 2 + (j - i - 1);
}

int ProblemSolver::dfs(int** matrix, int size) {
    // tworzymy stos
    std::stack<Node> frontier;
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest na stos
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki na stosie są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // zdejmujemy wierzchołek ze stosu
        Node node = frontier.top();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
         * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy na stos nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::dfsSym(int *symMatrix, int size) {
    // tworzymy stos
    std::stack<Node> frontier;
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest na stos
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki na stosie są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // zdejmujemy wierzchołek ze stosu
        Node node = frontier.top();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
         * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy na stos nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfs(int** matrix, int size) {
    // tworzymy kolejkę
    std::queue<Node> frontier;
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest do kolejki
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki w kolejce są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // wyciągamy wierzchołek z kolejki
        Node node = frontier.front();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
        * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy do kolejki nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsSym(int *symMatrix, int size) {
    // tworzymy kolejkę
    std::queue<Node> frontier;
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest do kolejki
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki w kolejce są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // wyciągamy wierzchołek z kolejki
        Node node = frontier.front();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
        * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy do kolejki nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZ(int** matrix, int size) {
    /* komparator sprawiający, że kolejka prioryterowa będzie najpierw umożliwiać wyciąganie
     * wierzchołków o najniższym koszcie dojścia */
    auto compBfsZ = [] (Node n1, Node n2) {
        return n1.cost > n2.cost;
    };
    // tworzymy kolejkę priorytetową
    std::priority_queue<Node, std::vector<Node>, decltype(compBfsZ)> frontier(compBfsZ);
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest do kolejki
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki w kolejce są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // wyciągamy wierzchołek z kolejki priorytetowej
        Node node = frontier.top();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            if(node.cost + matrix[node.curr][0] < best) best = node.cost + matrix[node.curr][0];
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
       * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBound(matrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy do kolejki priorytetowej nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i] && matrix[node.curr][i] != -1) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + matrix[node.curr][i], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}

int ProblemSolver::bfsZSym(int *symMatrix, int size) {
    /* komparator sprawiający, że kolejka prioryterowa będzie najpierw umożliwiać wyciąganie
     * wierzchołków o najniższym koszcie dojścia */
    auto compBfsZ = [] (Node n1, Node n2) {
        return n1.cost > n2.cost;
    };
    // tworzymy kolejkę priorytetową
    std::priority_queue<Node, std::vector<Node>, decltype(compBfsZ)> frontier(compBfsZ);
    // tworzymy wektor odwiedzonych i zaczynamy 0 jako odwiedzone
    std::vector<bool> visited(size, false);
    visited[0] = true;
    // konstruowany jest pierwszy wierzchołek i dodawany jest do kolejki
    Node first(0, 0, 1, visited);
    frontier.emplace(first);
    int best = INT_MAX;
    // dopoki w kolejce są wierzchołki to wykonujemy pętle
    while(!frontier.empty()) {
        // wyciągamy wierzchołek z kolejki priorytetowej
        Node node = frontier.top();
        frontier.pop();
        /* jeśli wierzchołek był ostatnim nieodwiedzonym
         * czyli miał głębokość == ilości miast
         * to sprawdzamy czy ma lepszy koszt niż najlepszy dotąd i ewentualnie zmieniamy */
        if(node.depth == size) {
            int newCost = node.cost + symMatrix[getSymIndex(node.curr, 0, size)];
            if(newCost < best) best = newCost;
            continue;
        }
        /* sprawdzamy ogarniczenie i jeśli zsumowane z obecnym kosztem dojścia jest
       * większe od aktualnie znalezionego najlepszego rozwiązania to odrzucamy gałąź */
        int bound = calculateBoundSym(symMatrix, node.visit, size);
        if(bound + node.cost >= best) continue;
        // dodajemy do kolejki priorytetowej nieodwiedzonych potomków wierzchołka
        for(int i = 0; i < size; i++) {
            if(!node.visit[i]) {
                node.visit[i] = true;
                frontier.emplace(i, node.cost + symMatrix[getSymIndex(node.curr, i, size)], node.depth + 1, node.visit);
                node.visit[i] = false;
            }
        }
    }
    return best;
}