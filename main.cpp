#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    Matrix<float> target(1,10);
    Matrix<float> query(1,5);


    target.generateRandomUniformMatrix(10);
    query.generateRandomUniformMatrix(10);

    //print_array(target.getValues(),target.getLength(),"target");
    //print_array(query.getValues(), query.getLength(),"query");

    PatternRecognition<float> pattern(query, target);
    pattern.findPattern();
    pattern.printPatterns();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << std::endl << float (duration/1000000.);

}
