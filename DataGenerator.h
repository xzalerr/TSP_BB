#ifndef TRAVELLINGSALESMANPROBLEMBRUTEFORCE_DATAGENERATOR_H
#define TRAVELLINGSALESMANPROBLEMBRUTEFORCE_DATAGENERATOR_H

#include <vector>
#include <string>

// Klasa do generowania losowych grafów
class DataGenerator {
public:
    std::vector<std::vector<int>> matrix;
    std::vector<int> symMatrix;

    // Funkcja generująca graf asymetryczny
    void generateDataAsymmetric(int n);

    // Funkcja generująca graf symetryczny
    void generateDataSymmetric(int n);

    // Funkcja wczytująca dane z zadanego pliku
    void loadData(std::string name, bool sym);

    // Funkcja wypisująca macierz na ekranie
    void printData(bool sym);
};


#endif //TRAVELLINGSALESMANPROBLEMBRUTEFORCE_DATAGENERATOR_H
