#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int n_argv_pos = 1;

float** matrix_malloc(int rows, int columns);
void free_matrix(float* matrix[], int rows);

void fill_matrix_a(int n, float* matrix_a[], char *argv[]);
void fill_array_b(int n, float* array_b, char *argv[]);

void show_matrix(float *matrix[], int width, int height);
void show_array(float array[], int size);


int main(int argc, char *argv[]) {
	int n = atoi(argv[n_argv_pos]);

	float** matrix_a = matrix_malloc(n, n);
	float* array_b = new float[n];

	fill_matrix_a(n, matrix_a, argv);
	fill_array_b(n, array_b, argv);

	show_matrix(matrix_a, n, n);
	cout << endl;
	show_array(array_b, n);

	delete[] array_b;
	free_matrix(matrix_a, n);
	
	return 0;
}

float** matrix_malloc(int rows, int columns) {
	float** matrix = new float*[rows];

	for (int i = 0; i < rows; i++) {
		matrix[i] = new float[columns];
	}

	return matrix;
}

void free_matrix(float* matrix[], int rows) {
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void fill_matrix_a(int n, float* matrix_a[], char *argv[]) {
	int current_argv_pos = n_argv_pos + 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix_a[i][j] = atoi(argv[current_argv_pos]);
			current_argv_pos++;
		}
	}
}

void fill_array_b(int n, float* array_b, char *argv[]) {
	int current_argv_pos = n_argv_pos + pow(n, 2) + 1;

	for (int i = 0; i < n; i++) {
		array_b[i] = atoi(argv[current_argv_pos]);
		current_argv_pos++;
	}
}

void show_matrix(float *matrix[], int width, int height) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cout << matrix[i][j] << ' ';
		}

		cout << endl;
	}
}

void show_array(float array[], int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i] << ' ';
	}

	cout << endl;
}