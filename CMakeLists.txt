cmake_minimum_required(VERSION 3.27)
project(TSP_BB)

set(CMAKE_CXX_STANDARD 20)

add_executable(TSP_BB main.cpp
        DataGenerator.h
        DataGenerator.cpp
        ProblemSolver.cpp
        ProblemSolver.h
        Config.cpp
        Config.h
        Runner.cpp
        Runner.h
)

include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.4
)
FetchContent_MakeAvailable(json)
target_link_libraries(TSP_BB nlohmann_json::nlohmann_json)
