#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
#include "ImageReader.h"


int main() {
    int trow = 1500;
    int tcol = 1500;
    int qrow = 150;
    int qcol = 150;
    for (int numThread = 1; numThread < 7; ++numThread) {
        auto t1 = std::chrono::high_resolution_clock::now();
        Matrix<int> target(trow, tcol);
        Matrix<int> query(qrow, qcol);

        target.generateRandomUniformMatrix(10);
        query.generateRandomUniformMatrix(10);
        for (int i = 0; i < 5; ++i) {
            PatternRecognition<int> pattern(query, target);
            pattern.findPattern(numThread);
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << std::endl << "Targetdim " << trow << "x" << tcol << "\tquerydim " << qrow << "x" << qcol
                  << "\twith numThread " << numThread << "  time:" << float(duration / 5000000.);
    }

    std::cout << std::endl << std::endl;

    trow = 2000;
    tcol = 2000;
    qrow = 200;
    qcol = 200;
    for (int numThread = 1; numThread < 7; ++numThread) {
        auto t1 = std::chrono::high_resolution_clock::now();
        Matrix<int> target(trow, tcol);
        Matrix<int> query(qrow, qcol);

        target.generateRandomUniformMatrix(10);
        query.generateRandomUniformMatrix(10);
        for (int i = 0; i < 5; ++i) {
            PatternRecognition<int> pattern(query, target);
            pattern.findPattern(numThread);
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << std::endl << "Targetdim " << trow << "x" << tcol << "\tquerydim " << qrow << "x" << qcol
                  << "\twith numThread " << numThread << "  time:" << float(duration / 5000000.);
    }

    std::cout << std::endl << std::endl;


    trow = 2500;
    tcol = 2500;
    qrow = 250;
    qcol = 250;
    for (int numThread = 1; numThread < 7; ++numThread) {
        auto t1 = std::chrono::high_resolution_clock::now();
        Matrix<int> target(trow, tcol);
        Matrix<int> query(qrow, qcol);

        target.generateRandomUniformMatrix(10);
        query.generateRandomUniformMatrix(10);
        for (int i = 0; i < 5; ++i) {
            PatternRecognition<int> pattern(query, target);
            pattern.findPattern(numThread);
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << std::endl << "Targetdim " << trow << "x" << tcol << "\tquerydim " << qrow << "x" << qcol
                  << "\twith numThread " << numThread << "  time:" << float(duration / 5000000.);
    }
}
