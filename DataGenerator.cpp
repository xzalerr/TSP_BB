#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

DataGenerator::~DataGenerator() {
    deallocateMatrix();
    deallocateSymMatrix();
}

void DataGenerator::allocateMatrix(int n) {
    deallocateMatrix();
    this->matrixSize = n;
    matrix = new int*[n];
    for(int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
}

void DataGenerator::allocateSymMatrix(int n) {
    deallocateSymMatrix();
    this->matrixSize = n;
    symMatrix = new int[(n*n-n)/2];
    symMatrixSize = (n*n-n)/2;
}

void DataGenerator::deallocateMatrix() {
    if (matrix != nullptr) {
        for (int i = 0; i < matrixSize; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
        matrixSize = 0;
    }
}

void DataGenerator::deallocateSymMatrix() {
    if (symMatrix != nullptr) {
        delete[] symMatrix;
        symMatrix = nullptr;
    }
    symMatrixSize = 0;
}

void DataGenerator::generateDataAsymmetric(int n) {
    // Utwórz generator losowych liczb z zakresu 1 - 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    // Wyczyść graf i zredefiniuj jego rozmiar
    allocateMatrix(n);
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
    allocateSymMatrix(n);
    for(int i = 0; i < (n*n-n)/2; i++) {
        symMatrix[i] = dist(gen);
    }
}

int DataGenerator::loadData(std::string name, bool sym) {
    // Otwórz plik o zadanej nazwie
    std::fstream input(name);

    if(!input.is_open()) {
        std::cerr << "Nie udało się zlokalizować pliku o podanej nazwie!\n";
        return -1;
    }
    // Z pierwszej linii wczytaj rozmiar instancji
    int n;
    input >> n;
    // Wyczyść graf i zredefiniuj jego rozmiar
    allocateMatrix(n);
    // Kolejne dane wczytuj w porządku wiersz po wierszu
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }
    input.close();
    if(sym) {
        allocateSymMatrix(n);
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                symMatrix[count] = matrix[i][j];
                count++;
            }
        }
        deallocateMatrix();
    }
    return n;
}

void DataGenerator::printData(bool sym) {
    if (!sym) {
        int n = this->matrixSize;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    } else {
        int n = 1;
        while((n*n-n)/2 < this->symMatrixSize) n++;
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

