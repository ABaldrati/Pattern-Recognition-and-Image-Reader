//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_SEQUENCE_H
#define PATTERN_RECOGNITION_SEQUENCE_H

#include "Utils.h"
#include <vector>
#include <ctime>
#include "Sequence.h"
#include <random>
#include <iostream>

template<typename T>
class Sequence {

public:

    Sequence(const int length) : length(length) {
        values = std::vector<int>(length);
    }


    void generateRandomUniformSequence(const T max_value) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_int_distribution<T> distribution(-max_value, max_value);
        for (int i = 0; i < length; i++) {
            values[i] = distribution(generator);
        }
    }


    int getLength() const {
        return length;
    }

    const std::vector<int> &getValues() const {
        return values;
    }

private:
    const int length;
    std::vector<int> values;

};


#endif //PATTERN_RECOGNITION_SEQUENCE_H
