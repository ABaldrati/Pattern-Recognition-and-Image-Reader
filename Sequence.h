//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_SEQUENCE_H
#define PATTERN_RECOGNITION_SEQUENCE_H


class Sequence {

public:

    explicit Sequence(int length, int max_value) : length(length), max_value(max_value){
        values = new int[length];
    }

    ~Sequence(){
        delete [] values;
    }


    void generate_random_uniform_sequence();


    int getLength() const;

    int *getValues() const;

private:
    int length;
    int max_value;
    int* values;

};


#endif //PATTERN_RECOGNITION_SEQUENCE_H
