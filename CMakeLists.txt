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
        headers/utils/Metrics.h
        src/utils/Metrics.cpp
        src/structures/Dataset.cpp
        headers/library.h
        tests/unit_tests/structures/vector/VectorTestFloat.cpp
        tests/unit_tests/structures/vector/VectorTestPoint.cpp
        tests/unit_tests/structures/vector/VectorTestNeighbor.cpp
        tests/unit_tests/structures/point/PointTest.cpp
        tests/unit_tests/structures/dataset/DatasetTest.cpp
        tests/unit_tests/structures/unorderedMap/UnorderedMapTest.cpp
        tests/unit_tests/structures/graph/GraphInitializationTest.cpp

        src/structures/point/PointInfo.cpp
        headers/utils/Statistics.h
        src/utils/Statistics.cpp
        headers/utils/StatisticInfo.h
        src/utils/StatisticInfo.cpp headers/structures/graph/Optimizations.h src/structures/graph/Optimizations.cpp headers/structures/randomProjectionTrees/RandomProjectionTrees.h src/structures/randomProjectionTrees/RandomProjectionTrees.cpp)
