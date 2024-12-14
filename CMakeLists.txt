cmake_minimum_required(VERSION 3.27)
project(TSP_BB)

set(CMAKE_CXX_STANDARD 20)

set(CONFIG_FILE_PATH "${CMAKE_SOURCE_DIR}/config.json")
if (EXISTS ${CONFIG_FILE_PATH})
    message(STATUS "Znaleziono config.json: ${CONFIG_FILE_PATH}")
    add_compile_definitions(CONFIG_FILE_PATH="${CONFIG_FILE_PATH}")
else()
    message(FATAL_ERROR "Plik config.json nie został znaleziony w ${CMAKE_SOURCE_DIR}!")
endif()

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
