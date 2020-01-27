//
// Created by alberto on 25/01/20.
//

#ifndef PATTERN_RECOGNITION_PATTERNRECOGNITION2D_H
#define PATTERN_RECOGNITION_PATTERNRECOGNITION2D_H

#include "Sequence.h"
#include "Utils.h"
#include <cmath>
#include <iostream>
#include "Matrix.h"

#ifdef _OPENMP
#include <omp.h>
#endif

template<typename T>
class PatternRecognition2D {
public:

    PatternRecognition2D(const Matrix<T> &query_matrix, const Matrix<T> &target_matrix) : query_matrix(
            query_matrix), target_matrix(target_matrix), nearest_matrix(
            Matrix<T>(query_matrix.getNumberOfRows(), query_matrix.getNumberOfColumns())), sads_matrix(
            Matrix<T>(target_matrix.getNumberOfRows() - query_matrix.getNumberOfColumns() + 1,
                      target_matrix.getNumberOfColumns() - query_matrix.getNumberOfColumns() + 1)) {
        top_left_coordinate = -1;
    }

    void findPattern() {

#pragma omp parallel for schedule(static) shared(sads, sads_length) default(none)

        for (int i = 0; i < sads_matrix.getNumberOfRows(); i++) {
            for (int j = 0; j < sads_matrix.getNumberOfColumns(); j++) {

                sads_matrix.setValue(i, j, 0);

                T difference_value = 0;
                for (int k = 0; k < query_matrix.getNumberOfRows(); k++) {
                    for (int l = 0; l < query_matrix.getNumberOfColumns(); l++) {

                        T target_value = target_matrix.getValue(i + k, j + l);
                        T query_value = query_matrix.getValue(k, l);
                        difference_value += std::abs(target_value - query_value);

                    }
                }
                sads_matrix.setValue(i, j, difference_value);
            }
        }

        top_left_coordinate = minElementVector(sads_matrix.getValues());
        int cx = top_left_coordinate / sads_matrix.getNumberOfColumns();
        int cy = top_left_coordinate % sads_matrix.getNumberOfColumns();

        for (int i = 0; i < nearest_matrix.getNumberOfRows(); ++i) {
            for (int j = 0; j < nearest_matrix.getNumberOfColumns(); ++j) {
                T nearest_value = target_matrix.getValue(i + cx, j + cy);
                nearest_matrix.setValue(i, j, nearest_value);
            }
        }
    }



    void printPatterns() {
        std::cout<< std::endl <<"TL coordinate " << top_left_coordinate;
        printMatrix(target_matrix.getValues(), target_matrix.getNumberOfRows(), target_matrix.getNumberOfColumns(), "target");
        printMatrix(query_matrix.getValues(), query_matrix.getNumberOfRows(), query_matrix.getNumberOfColumns(), "query");
        printMatrix(sads_matrix.getValues(), sads_matrix.getNumberOfRows(), sads_matrix.getNumberOfColumns(), "sads");
        printMatrix(nearest_matrix.getValues(), nearest_matrix.getNumberOfRows(), nearest_matrix.getNumberOfColumns(), "nearest");
    }

    const Matrix<T> &getQueryMatrix() const {
        return query_matrix;
    }

    const Matrix<T> &getTargetMatrix() const {
        return target_matrix;
    }

    const Matrix<T> &getSadsMatrix() const {
        return sads_matrix;
    }

    const Matrix<T> &getNearestMatrix() const {
        return nearest_matrix;
    }

    int getTopLeftCoordinate() const {
        return top_left_coordinate;
    }

private:
    const Matrix<T> &query_matrix;
    const Matrix<T> &target_matrix;
    Matrix<T> sads_matrix;
    Matrix<T> nearest_matrix;
    int top_left_coordinate;
};

#endif //PATTERN_RECOGNITION_PATTERNRECOGNITION2D_H
