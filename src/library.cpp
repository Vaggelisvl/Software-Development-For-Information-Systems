#include <cstdio>
//#include <cstdint>
#include <iostream>
//#include <fstream>


using namespace std;


uint32_t readElementsFromFile(const char* filename, float* elements) {
    uint32_t N;

    FILE *file = fopen(filename, "rb");

    if (!file) {
        fprintf(stderr, "Unable to open file\n");
        return 0;
    }

    fread(&N, sizeof(uint32_t), 1, file);

    fread(elements, sizeof(float), N * 100, file);



    // Now you can use the elements array

    fclose(file);
    return N;
}

int main(){
    float *elements = new float[100 * 100];
    uint32_t N = readElementsFromFile("input1.bin",elements);

    for (int i = 0; i < N; i++) {
        cout << "Element " << i + 1 << ":\n";
        for (int j = 0; j < 100; j++) {
            cout << elements[i * 100 + j] << " " << endl;
        }
        cout << endl;
    }

    delete[] elements;

}
