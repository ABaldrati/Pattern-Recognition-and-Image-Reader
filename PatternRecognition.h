//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_PATTERNRECOGNITION_H
#define PATTERN_RECOGNITION_PATTERNRECOGNITION_H

#include "Sequence.h"
#include "Utils.h"

class PatternRecognition {

    PatternRecognition(Sequence query_sequence, Sequence target_sequence) : query_sequence(query_sequence),
                                                                            target_sequence(target_sequence) {
    }

    void findPattern();


private:
    Sequence query_sequence;
    Sequence target_sequence;
    int begin;
};


#endif //PATTERN_RECOGNITION_PATTERNRECOGNITION_H
