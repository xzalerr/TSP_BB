#include <iostream>
#include <chrono>
#include "DataGenerator.h"
#include "ProblemSolver.h"
#include "Config.h"
#include "Runner.h"

int main() {
    Config config;
    config.loadData("/Users/rafalzalecki/CLionProjects/TSP_BB/config.json");

    DataGenerator generator;
    ProblemSolver ps;
    Runner runner(config, generator, ps);

    if (config.mode == "test") {
        runner.executeTest();
    } else if (config.mode == "simulation") {
        runner.executeSimulation();
    } else {
        std::cerr << "Nie ma takiej opcji!\n";
    }

    return 0;
}
