/*
 * Utils.h
 *
 *  Created on: 12/feb/2020
 *      Author: alberto
 */

#ifndef UTILS_H_
#define UTILS_H_

float* generateRandomUniformMatrix(int size, const float max_value) {
	float* matrix = new float[size];
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_real_distribution<float> distribution(0, max_value);
	for (int i = 0; i < size; i++) {
		matrix[i] = distribution(generator);
	}
	return matrix;
}

void printMatrix(const float * matrix, const int rows, const int columns, const std::string& name = "") {
	std::cout << std::endl << name << " " << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << matrix[columns * i + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool check_correctness(const float* target_matrix, const float* query_matrix, const float *sads_matrix, int target_rows, int target_columns,
		int query_rows, int query_columns, int sads_rows, int sads_columns) {

	bool equal = true;

	for (int i = 0; i < sads_rows; i++) {
		for (int j = 0; j < sads_columns; j++) {

			float difference_value = 0;

			for (int k = 0; k < query_rows; k++) {
				for (int l = 0; l < query_columns; l++) {

					float target_value = target_matrix[(i + k) * target_columns + j + l];
					float query_value = query_matrix[k * query_columns + l];
					difference_value += std::abs(target_value - query_value);

				}
			}
			if (std::abs(sads_matrix[i * sads_columns + j] - difference_value) > 2) {
				equal = false;
				break;
			}

		}
	}
	return equal;
}

int minElementMatrix(const float* matrix, const int r, const int c) {
    int min_el = 0;
    for (int i = 0; i < r *c ; ++i) {
        if (matrix[i] < matrix[min_el]) {
            min_el = i;
        }
    }
    return min_el;
}

#endif /* UTILS_H_ */
