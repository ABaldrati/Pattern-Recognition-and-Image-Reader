//
// Created by alberto on 21/01/20.
//
#include <ctime>
#include "Sequence.h"
#include <random>
#include <iostream>


void Sequence::generateRandomUniformSequence() {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(-max_value, max_value);
    for (int i = 0; i < length; i++) {
        values[i] = distribution(generator);
    }
}

int Sequence::getLength() const {
    return length;
}

const std::vector<int> &Sequence::getValues() const {
    return values;
}
