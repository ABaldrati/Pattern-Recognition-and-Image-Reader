#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
#include "ImageReader.h"


int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    Matrix<int> target(1500,1500);
    Matrix<int> query(100, 100);

    target.generateRandomUniformMatrix(25);
    query.generateRandomUniformMatrix(25);

    PatternRecognition<int> pattern(query, target);
    pattern.findPattern();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << std::endl << float(duration / 1000000.);

}
