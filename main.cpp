#include <iostream>
#include <zconf.h>
#include "Sequence.h"
#include "PatternRecognition.h"
#include "Utils.h"
#include <chrono>
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    Sequence<int> target(100);
    Sequence<int> query(5);


    target.generateRandomUniformSequence(10);
    query.generateRandomUniformSequence(10);

    //print_array(target.getValues(),target.getLength(),"target");
    //print_array(query.getValues(), query.getLength(),"query");

    PatternRecognition<int> pattern(query,target);
    pattern.findPattern();
    pattern.PrintPattern();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << std::endl << float (duration/1000000.);

}
