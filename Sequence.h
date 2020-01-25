//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_SEQUENCE_H
#define PATTERN_RECOGNITION_SEQUENCE_H

#include "Utils.h"
#include <vector>
#include <ctime>
#include <random>
#include <iostream>

template<typename T>
class Sequence {

public:

    explicit Sequence(const int length) {
        values = std::vector<T>(length);
    }

    void generateRandomUniformSequence(const T max_value) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_real_distribution<T> distribution(-max_value, max_value);
        for (int i = 0; i < values.size(); i++) {
            values[i] = distribution(generator);
        }
    }

    const std::vector<T> &getValues() const {
        return values;
    }

private:
    std::vector<T> values;

};

#endif //PATTERN_RECOGNITION_SEQUENCE_H
