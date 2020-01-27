//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_UTILS_H
#define PATTERN_RECOGNITION_UTILS_H

#include <iostream>
#include <string>
#include <vector>

template<typename T>
int minElementVector(const std::vector<T> vector){
    int min_el=0;
    for (int i=0;i<vector.size();i++){
        if(vector[i] < vector[min_el]){
            min_el = i;
        }
    }
    return min_el;
}

template<typename T>
void print_array(const T* array, const int lenght,const std::string& name=""){
    std::cout << std::endl << name << " ";
    for(int i=0;i<lenght;i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

#endif //PATTERN_RECOGNITION_UTILS_H
