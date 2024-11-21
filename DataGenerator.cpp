#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

void DataGenerator::generateDataAsymmetric(int n) {
    // Utwórz generator losowych liczb z zakresu 1 - 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    // Wyczyść graf i zredefiniuj jego rozmiar
    matrix.clear();
    matrix.resize(n, std::vector<int>(n));
    // Przypisz do grafu losowe wartości, poza przekątną gdzie jest -1
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) this->matrix[i][j] = -1;
            else this->matrix[i][j] = dist(gen);
        }
    }
}

void DataGenerator::generateDataSymmetric(int n) {
    // Utwórz generator losowych liczb z zakresu 1 - 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    // Wyczyść graf i zredefiniuj jego rozmiar
    symMatrix.clear();
    int size = (n*n-n)/2;
    for(int i = 0; i < size; i++) {
        symMatrix.emplace_back(dist(gen));
    }
}

void DataGenerator::loadData(std::string name, bool sym) {
    // Otwórz plik o zadanej nazwie
    std::fstream input(name);

    if(!input.is_open()) {
        std::cerr << "Nie udało się zlokalizować pliku o podanej nazwie!\n";
        return;
    }
    // Z pierwszej linii wczytaj rozmiar instancji
    int n;
    input >> n;
    // Wyczyść graf i zredefiniuj jego rozmiar
    matrix.clear();
    matrix.resize(n, std::vector<int>(n));
    // Kolejne dane wczytuj w porządku wiersz po wierszu
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }
    input.close();
    if(sym) {
        symMatrix.clear();
        symMatrix.resize((n*n-n)/2, 0);
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                symMatrix[count] = matrix[i][j];
                count++;
            }
        }
    }
}

void DataGenerator::printData(bool sym) {
    if (!sym) {
        int n = this->matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    } else {
        int n = 1;
        while((n*n-n)/2 < symMatrix.size()) n++;
        int index = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    std::cout << std::setw(3) << -1 << " ";
                } else if (i < j) {
                    std::cout << std::setw(3) << symMatrix[index++] << " ";
                } else {
                    std::cout << std::setw(4) << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

