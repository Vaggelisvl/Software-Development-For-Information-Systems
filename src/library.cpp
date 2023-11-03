#include <iostream>
#include <fstream>

#include "../headers/structures/vector/Vector.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/point/Point.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/GraphInitialization.h"


#include "../src/structures/vector/Vector.cpp"
#include "../src/structures/unorderedMap/UnorderedMap.cpp"
#include "../src/structures/point/Point.cpp"
#include "../src/config/Logger.cpp"
#include "../src/structures/GraphInitialization.cpp"



uint32_t readVectorFromFile(const char* filename, Vector<Point>& elements) {
    uint32_t N;

    FILE* file = fopen(filename, "rb");

    if (!file) {
        fprintf(stderr, "Unable to open file\n");
        return 0;
    }

    fread(&N, sizeof(uint32_t), 1, file);
    int num=0;
    // Reserve capacity in the Vector to accommodate N elements.
    elements.reserve(N);
    for (uint32_t i = 0; i < N; i++) {
        Vector<float> coordinates;
        for(int j=0;j<100;j++){
            float element;  // Use the same type as the Vector
            fread(&element, sizeof(float ), 1, file);
//            std::cout<<element<<std::endl;
            coordinates.push_back(element);
        }
        elements.push_back(Point(++num, coordinates));

    }
    fclose(file);
    return N;
}
using namespace std;
int main() {
    Vector<Point> elements;
    uint32_t N = readVectorFromFile("input1.bin", elements);
    std::cout<<N<<std::endl;
    for(int i=0;i<N;i++){
        cout<<"\n\n\n\n"<<endl;
        cout<<"vector element: "<<elements.at(i).getId()<<endl;
        elements.at(i).getCoordinates().print();
    }

    //initialize graph, put points, set K, initialize random k neighbors
    GraphInitialization g;
    for(int i=0;i<N;i++){
        g.putPoints(elements.at(i).getCoordinates());
    }
    g.initializeK();
    cout<<"numofpoint="<<g.getNumOfPoints()<<endl;
    g.setKRandomNeighbors();
}