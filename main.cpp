#include <iostream>
#include <chrono>
#include "DataGenerator.h"
#include "ProblemSolver.h"
#include "Config.h"
#include "Runner.h"

namespace fs = std::filesystem;

int main() {
    Config config;
    std::string path = CONFIG_FILE_PATH;
    config.loadData(path);

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
