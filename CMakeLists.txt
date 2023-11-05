cmake_minimum_required(VERSION 3.23)
project(_project)

set(CMAKE_CXX_STANDARD 17)

add_library(_project
        headers/structures/unorderedMap/UnorderedMap.h
        src/config/Logger.cpp
        headers/config/Logger.h
        headers/structures/vector/Vector.h
        headers/structures/graph/GraphInitialization.h
        src/structures/graph/GraphInitialization.cpp
        headers/structures/point/Point.h
        headers/structures/point/Neighbors.h
        src/structures/point/Neighbors.cpp
        src/structures/point/Point.cpp
        src/library.cpp headers/structures/Dataset.h
        headers/Metrics.h
        src/Metrics.cpp
        src/structures/Dataset.cpp
        headers/library.h)
