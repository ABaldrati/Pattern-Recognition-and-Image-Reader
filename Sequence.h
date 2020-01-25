//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_SEQUENCE_H
#define PATTERN_RECOGNITION_SEQUENCE_H

#include "Utils.h"
#include <vector>

class Sequence {

public:

    Sequence(const int length, const int max_value) : length(length), max_value(max_value) {
        values = std::vector<int>(length);
    }


    void generateRandomUniformSequence();

    int getLength() const;

    const std::vector<int> &getValues() const;

private:
    const int length;
    const int max_value;
    std::vector<int> values;

};


#endif //PATTERN_RECOGNITION_SEQUENCE_H
