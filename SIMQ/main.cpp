#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct simq_result {
	float* solution;
	int error;
};

const int n_argv_pos = 1;

float** matrix_malloc(int rows, int columns);
void free_matrix(float* matrix[], int rows);

void fill_matrix_a(int n, float* matrix_a[], char *argv[]);
void fill_array_b(int n, float array_b[], char *argv[]);

void show_matrix(float* matrix[], int rows, int cols);
void show_array(float array[], int size);

void arrcpy(int n, float array_dest[], float array_src[]);
void matrcpy(int rows, int columns, float* matrix_dest[], float* matrix_src[]);

simq_result* simq(int n, float* matrix_a[], float array_b[]);

// Command line arguments format: 
// <n as matrix_dimensions> <matrix_a[0, 0]...matrix_a[n, n]> <array_b[0]...array_b[n]>
//
// Example:
// n = 3; matrix_a = [[1, 1, 1], [1, 0, -1], [1, 2, 1]]; matrix_b = [6, -2, 3]
//
// Command line:
// 3 1 1 1 1 0 -1 1 2 1 6 -2 3

int main(int argc, char *argv[]) {
	int n = atoi(argv[n_argv_pos]);

	float** matrix_a = matrix_malloc(n, n);
	fill_matrix_a(n, matrix_a, argv);

	float* array_b = new float[n];
	fill_array_b(n, array_b, argv);

	show_matrix(matrix_a, n, n);
	cout << endl;

	show_array(array_b, n);
	cout << endl;

	simq_result* result;
	result = simq(n, matrix_a, array_b);

	delete[] result->solution;
	delete[] result;
	delete[] array_b;
	free_matrix(matrix_a, n);
	
	return 0;
}

simq_result* simq(int n, float* matrix_a[], float array_b[]) {
	simq_result* result = new simq_result;
	result->solution = new float[n];

	float** extended_matrix = matrix_malloc(n, n + 1);
	matrcpy(n, n, extended_matrix, matrix_a);

	for (int i = 0; i < n; i++) {
		extended_matrix[i][n] = array_b[i];
	}

	show_matrix(extended_matrix, n, n + 1);
	cout << endl;

	return result;
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

void fill_array_b(int n, float array_b[], char *argv[]) {
	int current_argv_pos = n_argv_pos + pow(n, 2) + 1;

	for (int i = 0; i < n; i++) {
		array_b[i] = atoi(argv[current_argv_pos]);
		current_argv_pos++;
	}
}

void show_matrix(float* matrix[], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		show_array(matrix[i], cols);
	}
}

void show_array(float array[], int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i] << ' ';
	}

	cout << endl;
}

void matrcpy(int rows, int columns, float* matrix_dest[], float* matrix_src[]) {
	for (int i = 0; i < rows; i++) {
		arrcpy(columns, matrix_dest[i], matrix_src[i]);
	}
}

void arrcpy(int n, float array_dest[], float array_src[]) {
	for (int i = 0; i < n; i++) {
		array_dest[i] = array_src[i];
	}
}