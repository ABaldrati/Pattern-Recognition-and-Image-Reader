//
// Created by alberto on 25/01/20.
//

#ifndef PATTERN_RECOGNITION_MATRIX_H
#define PATTERN_RECOGNITION_MATRIX_H

#include <vector>
#include <iostream>
#include <random>

template<typename T>
class Matrix {
public:

    Matrix(int r, int c) : rows(r), columns(c) {
        if (r < 1)
            rows = 1;
        if (c < 1)
            columns = 1;
        values = std::vector<T>(rows * columns);
    }

    Matrix(const Matrix &rh) {
        rows = rh.rows;
        columns = rh.columns;
        values = std::vector<T>(rows * columns);
        for (int i = 0; i < rows * columns; i++)
            values[i] = rh.values[i];
    }

    void generateRandomUniformMatrix(const T max_value) {
        return _generateRandomUniformMatrix(max_value, std::is_floating_point<T>());
    }

    int getNumberOfRows() const {
        return rows;
    }

    int getNumberOfColumns() const {
        return columns;
    }

    const std::vector<T> &getValues() const {
        return values;
    }

    T getValue(int i, int j) const {
        if (i >= rows || i < 0 || j < 0 || j >= columns) {
            throw std::out_of_range("Elemento non presente nella matrice read");
        }
        return values[columns * i + j];
    }

    void setValue(int i, int j, const T &value) {
        if (i >= rows || j >= columns) {
            throw std::out_of_range("Elemento non presente nella matrice write");
        }
        values[columns * i + j] = value;
    }


private:
    std::vector<T> values;
    int rows;
    int columns;

    void _generateRandomUniformMatrix(const T max_value,  std::false_type) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_int_distribution<T> distribution(-max_value, max_value);
        for (int i = 0; i < rows * columns; i++) {
            values[i] = distribution(generator);
        }
    }

    void _generateRandomUniformMatrix(const T max_value,  std::true_type) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_real_distribution<T> distribution(-max_value, max_value);
        for (int i = 0; i < rows * columns; i++) {
            values[i] = distribution(generator);
        }
    }

};

#endif //PATTERN_RECOGNITION_MATRIX_H
