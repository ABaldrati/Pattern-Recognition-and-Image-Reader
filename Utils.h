//
// Created by alberto on 21/01/20.
//

#ifndef PATTERN_RECOGNITION_UTILS_H
#define PATTERN_RECOGNITION_UTILS_H

template<typename T>
int min_element_array(const T* array, const int length){
    int min_el=array[0];
    for (int i=0;i<length;i++){
        if(array[i]<min_el){
            min_el = array[i];
        }
    }
}

#endif //PATTERN_RECOGNITION_UTILS_H