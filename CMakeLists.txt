cmake_minimum_required(VERSION 3.23)
project(_project)

set(CMAKE_CXX_STANDARD 17)

add_library(_project
        src/structures/unorderedMap/UnorderedMap.cpp
        headers/structures/unorderedMap/UnorderedMap.h

        src/config/Logger.cpp
        headers/config/Logger.h
        headers/structures/vector/Vector.h
        src/structures/vector/Vector.cpp headers/structures/GraphInitialization.h src/GraphInitialization.cpp)
