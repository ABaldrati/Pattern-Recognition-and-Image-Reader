//
// Created by alberto on 21/01/20.
//

#include <cmath>
#include <iostream>
#include "PatternRecognition.h"

#ifdef _OPENMP
#include <omp.h>
#endif

void PatternRecognition::findPattern() {
    int sads_length = target_sequence.getLength() - query_sequence.getLength() + 1;
    int *sads = new int[sads_length];
#pragma omp parallel for schedule(static) shared(sads, sads_length) default(none)
    for (int i = 0; i < sads_length; i++) {
        sads[i] = 0;
        for (int j = 0; j < query_sequence.getLength(); j++) {
            std::cout << "target = " << target_sequence.getValues() << std::endl;
            int i1 = target_sequence.getValues()[i + j];
            int i2 = query_sequence.getValues()[j];

            sads[i] += std::abs(i1 - i2);
        }
    }

    std::cout << std::endl << "sads ";
    for (int i = 0; i < target_sequence.getLength() - query_sequence.getLength() + 1; i++) {
        std::cout << sads[i] << " ";
    }
    std::cout << std::endl;

    begin = min_element_array(sads, sads_length);
}

void PatternRecognition::PrintPattern() {
    for (int i = begin; i < begin + query_sequence.getLength(); i++) {
        std::cout << target_sequence.getValues()[i] << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i < query_sequence.getLength(); i++) {
        std::cout << query_sequence.getValues()[i] << " ";
    }

}
