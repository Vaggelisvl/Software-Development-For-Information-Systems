cmake_minimum_required(VERSION 3.23)
project(_project)

set(CMAKE_CXX_STANDARD 17)

add_library(_project
        src/structures/unorderedMap/UnorderedMap.cpp
        headers/structures/unorderedMap/UnorderedMap.h
        src/config/Logger.cpp
        headers/config/Logger.h
        headers/structures/vector/Vector.h
        src/structures/vector/Vector.cpp
        headers/structures/GraphInitialization.h
        src/structures/GraphInitialization.cpp
        headers/structures/point/Point.h
        headers/structures/point/Neighbors.h
        src/structures/point/Neighbors.cpp
        src/structures/point/Point.cpp
        src/library.cpp headers/structures/GraphAlgorithm.h src/structures/GraphAlgorithm.cpp headers/structures/Dataset.h src/structures/Dataset.cpp)
