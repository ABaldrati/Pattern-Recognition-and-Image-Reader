//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_SEQUENCE_H
#define PATTERN_RECOGNITION_SEQUENCE_H


class Sequence {

public:
    explicit Sequence(int length, int max_value) : length(length), max_value(max_value){
        values = new int[length]
    }

    void generate_random_sequence();


private:
    int length;
    int max_value;
    int* values;

};


#endif //PATTERN_RECOGNITION_SEQUENCE_H
