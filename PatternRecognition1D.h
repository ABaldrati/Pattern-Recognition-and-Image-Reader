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

    PatternRecognition1D(const Sequence<T> &query_sequence, const Sequence<T> &target_sequence) : query_sequence(
            query_sequence), target_sequence(target_sequence) {
        offset_begin = 0;

        nearest_vector = std::vector<T>(query_sequence.getValues().size());

        int sads_length = target_sequence.getValues().size() - query_sequence.getValues().size() + 1;
        sads_vector = std::vector<T>(sads_length);
    }

    void findPattern() {
#pragma omp parallel for schedule(static) shared(sads, sads_length) default(none)
        for (int i = 0; i < sads_vector.size(); i++) {
            sads_vector[i] = 0;
            for (int j = 0; j < query_sequence.getValues().size(); j++) {
                T target_value = target_sequence.getValues()[i + j];
                T query_value = query_sequence.getValues()[j];

                sads_vector[i] += std::abs(target_value - query_value);
            }
        }

        offset_begin = minElementVector(sads_vector);

        for (int i = 0; i < nearest_vector.size() ; ++i) {
            nearest_vector[i] = target_sequence.getValues()[i+offset_begin];
        }


    }

    void printPatterns() {
        printVector(target_sequence.getValues(),"target");
        printVector(query_sequence.getValues(),"query");
        printVector(sads_vector,"sads");
        printVector(nearest_vector, "nearest");
    }

    const std::vector<T> &getSadsVector() const {
        return sads_vector;
    }

    const Sequence<T> &getQuerySequence() const {
        return query_sequence;
    }

    const Sequence<T> &getTargetSequence() const {
        return target_sequence;
    }

    const std::vector<T> &getNearestVector() const {
        return nearest_vector;
    }

    int getOffsetBegin() const {
        return offset_begin;
    }

private:
    const Sequence<T> &query_sequence;
    const Sequence<T> &target_sequence;
    std::vector<T> sads_vector;
    std::vector<T> nearest_vector;
    int offset_begin;
};


#endif //PATTERN_RECOGNITION_PATTERNRECOGNITION_H
