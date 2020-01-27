//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_PATTERNRECOGNITION_H
#define PATTERN_RECOGNITION_PATTERNRECOGNITION_H

#include "Sequence.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

#ifdef _OPENMP
#include <omp.h>
#endif

template<typename T>
class PatternRecognition1D {
public:

    PatternRecognition(const Sequence<T> &query_sequence, const Sequence<T> &target_sequence) : query_sequence(
            query_sequence), target_sequence(target_sequence) {
        begin = 0;
    }

    void findPattern() {
        int sads_length = target_sequence.getValues().size() - query_sequence.getValues().size() + 1;
        T *sads = new T[sads_length];
#pragma omp parallel for schedule(static) shared(sads, sads_length) default(none)
        for (int i = 0; i < sads_length; i++) {
            sads[i] = 0;
            for (int j = 0; j < query_sequence.getValues().size(); j++) {
                T target_value = target_sequence.getValues()[i + j];
                T query_value = query_sequence.getValues()[j];

                sads[i] += std::abs(target_value - query_value);
            }
        }

        std::cout << std::endl << "sads ";
        for (int i = 0; i < sads_length; i++) {
            std::cout << sads[i] << " ";
        }
        std::cout << std::endl;

        begin = min_element_array(sads, sads_length);
    }

    void PrintPattern() {
        for (int i = begin; i < begin + query_sequence.getValues().size(); i++) {
            std::cout << target_sequence.getValues()[i] << " ";
        }

        std::cout << std::endl;

        for (int i = 0; i < query_sequence.getValues().size(); i++) {
            std::cout << query_sequence.getValues()[i] << " ";
        }
    }


private:
    const Sequence<T> &query_sequence;
    const Sequence<T> &target_sequence;
    int begin;
};


#endif //PATTERN_RECOGNITION_PATTERNRECOGNITION_H
