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

    explicit Sequence(int initial_length) {
        values = std::vector<T>(initial_length);
    }

    Sequence(const Sequence &rh) {
        int size = rh.getValues().size();
        values = std::vector<T>(size);
        for (int i = 0; i < size; i++)
            values[i] = rh.values[i];
    }

    void generateRandomUniformSequence(const T max_value) {
        return _generateRandomUniformSequence(max_value, std::is_floating_point<T>());
    }

    void _generateRandomUniformSequence(const T max_value, std::false_type) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_int_distribution<T> distribution(-max_value, max_value);
        for (int i = 0; i < values.size(); i++) {
            values[i] = distribution(generator);
        }
    }

    void _generateRandomUniformSequence(const T max_value, std::true_type) {
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
