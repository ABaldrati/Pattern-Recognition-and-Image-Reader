//
// Created by alberto on 21/01/20.
//

#include "Sequence.h"
#include <random>
void Sequence::generate_random_sequence() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-max_value,max_value);
    for(int i=0;i<length;i++){
        values[i]=distribution(generator)
    }

}
