#include <stdio.h>
#include <math.h>

/*
    Sample answers Produced by a student
*/


void task_2() {
	// Исходный массив
	int array[10] = {1, 2, 0, 5, 0, 1, 0, 0, 4, 3};
	int size = 10;
	////////////
	int attemps = 0;
	while (attemps < size) {
		if (array[attemps] == 0) {
			int shift_count = attemps;
			while (shift_count < size - 1) {
				array[shift_count] = array[shift_count + 1];
				shift_count += 1;
			}
			size -= 1;
		} else {
			attemps += 1;
		}	
	}
	printf("%d\n", size);
	int count = 0;
	while (count < 10) {
		printf("%d ", array[count]);
		count += 1;
	}
}

void task_3() {
	// Исходный массив
	float array[10] = {1.5, 2.76, 0.09, 5.23, 0.1, 11.0, 0.20, 50.0, 40, 31.9};	
	int size = 10;
	//////////////
	float average = 0;
	int attemp = 0;
	while (attemp < size) {
		average += array[attemp];
		attemp += 1;
	}
	average /= size;
	int attemps = 0;
	while (attemps < size) {
		float difference = 0;
		difference = array[attemps] - average;
		printf("%f\n", difference);
		attemps += 1; 
	}
}

double factorial(int n) {
	int count = 1;
	double product = 1;
	while (count <= n) {
		product *= count;
		count += 1;
	}
	printf("%d! = %f\n", n, product);
	return product;
}
 
void task_6() {
	// Исходный массив
	double array[25];
	int size = 25;
	/////
	double e = 0;
	int count = 0;
	while (count < size) {
		array[count] = 1 / factorial(count);
		e += array[count];
		// printf("%f", array[count]);
		count += 1;
	}
	printf("%f", exp(1));
	printf("%f", e);
}

void task_7() {
	// Исходный массив
	int array[10] = {10, -2, 10, 25, 9, 2, 1, 9, 1, -5};
	int size = 10;
	/////////////
	int attemps = 1;
	while (attemps < size) {
		array[attemps] = array[attemps] * array[attemps - 1];
		attemps += 1;
	}
	int attempt = 0;
	while(attempt < size) {
		printf("%d ", array[attempt]);
		attempt += 1;
	}
}

void task_8() {
	// Исходный массив
	// int array[10] = {1, 2, 2, 5, 0, 1, 0, 0, 9, 9};
	int array[10] = {1, 2, 3, 5, 0, 1, 0, 2, 9, 7};
	int size = 10;
	////////
	int attemps = 0;
	while (attemps < size) { 
		if (array[attemps] != array[attemps + 1]) {
			attemps += 1;
		} else {
			int shift_count = attemps;
			while (shift_count < size - 1) {
				array[shift_count] = array[shift_count + 1];
				shift_count += 1;
			}
			size -= 1;
			attemps += 1;
		}
	}
	printf("%d\n", size);
	int count = 0;
	while (count < size) {
		printf("%d ", array[count]);
		count += 1;
	}
}

int main() {
	/// task_2();
	/// task_3();
	// task_6();
	task_7();
	/// task_8();
}