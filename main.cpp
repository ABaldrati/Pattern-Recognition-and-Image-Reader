#include <iostream>
#include <zconf.h>
#include "Sequence.h"
#include "PatternRecognition.h"
#include "Utils.h"
#include <chrono>
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    Sequence target = Sequence(100000,20);
    Sequence query = Sequence(500,20);

    target.generateRandomUniformSequence();
    query.generateRandomUniformSequence();

    //print_array(target.getValues(),target.getLength(),"target");
    //print_array(query.getValues(), query.getLength(),"query");

    std::cout << "target = " << target.getValues() << std::endl;

    PatternRecognition pattern = PatternRecognition(query, target);
    pattern.findPattern();
    pattern.PrintPattern();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << std::endl << duration/1000000;

}
