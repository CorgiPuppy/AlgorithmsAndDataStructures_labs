#include <iostream>
#include <random>
#include <chrono>

#include "../include/Constants.h"

void insertionSort(double [], int, int&, int&);
void generationArray(double [], int);

int main() {
	for (int episode = 0; episode < Constants::M; episode++) {
		int size = Constants::sizes[episode];
		double* array = new double[size];

		for (int attempt = 0; attempt < Constants::amount_of_attempts; attempt++) {
			int amount_of_repeated_passes = 0;
			int amount_of_swaps = 0;

			generationArray(array, size);
			
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			insertionSort(array, size, amount_of_repeated_passes, amount_of_swaps);	

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::micro> micro_diff = end - start;

			std::cout << std::endl << "Time: " << micro_diff.count() << " micro sec." << std::endl;
			std::cout << "Количество повторных прохождений по массиву: " << amount_of_repeated_passes << ";" << std::endl;
			std::cout << "Количество выполнения операций обмена значений: " << amount_of_swaps << "." << std::endl;
		}

		delete [] array;
	}

	return 0;
}

void insertionSort(double array[], int size, int& repeated_passes, int& swaps) {
	for (int i = 1; i < size; i++) {
		repeated_passes++;

		int j = i - 1;
		while (j > -1 && array[j] > array[j + 1]) {
			double temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;

			swaps++;

			j--;
		}
	}
}

void generationArray(double array[], int size) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_real_distribution<double> gen(-1.0, 1.0);

	for (int i = 0; i < size; i++)
		array[i] = gen(engine);
}
