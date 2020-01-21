//
// Created by alberto on 21/01/20.
//

#include <cmath>
#include <iostream>
#include "PatternRecognition.h"

void PatternRecognition::findPattern() {
    int* sads = new int[target_sequence.getLength()-query_sequence.getLength()+1];
    for(int i=0;i<target_sequence.getLength()-query_sequence.getLength()+1;i++){
        sads[i]=0;
        for(int j=0;j<query_sequence.getLength();j++){
            sads[i]+=std::abs(target_sequence.getValues()[i+j]-query_sequence.getValues()[j]);
        }
    }

    begin = min_element_array(sads,target_sequence.getLength()-query_sequence.getLength()+1);
}

void PatternRecognition::PrintPattern() {
    for (int i=begin;i<begin + query_sequence.getLength();i++){
        std::cout << target_sequence.getValues()[i] << " ";
    }

    std::cout << std::endl;

    for (int i=0;i<query_sequence.getLength();i++){
        std::cout << query_sequence.getValues()[i] << " ";
    }

}
