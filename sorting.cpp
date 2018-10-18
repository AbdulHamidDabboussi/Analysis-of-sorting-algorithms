#include <ctime>
#include <iostream>
#include "sorting.h"
using namespace std;

void merge(int * arr, int first, int mid, int last, int & compCount, int & moveCount) {
	int * tempArr = new int[last + 1]; //temp array

	int first1 = first; 	// beginning of first subarray
	int last1 = mid; 		// end of first subarray
	int first2 = mid + 1;	// beginning of second subarray
	int last2 = last;		// end of second subarray
	int index = first1;		// next available location in tempArray

	for (; first1 <= last1 && first2 <= last2; index++) {
		if (arr[first1] < arr[first2]) {
			tempArr[index] = arr[first1];
			first1++;
		}
		else {
			tempArr[index] = arr[first2];
			first2++;
		}
		compCount++;
		moveCount++;
	}

	//if second array is exhausted
	for (; first1 <= last1; first1++, index++) {
		tempArr[index] = arr[first1];
		moveCount++;
	}

	//if first array is exhausted
	for (; first2 <= last2; first2++, index++) {
		tempArr[index] = arr[first2];
		moveCount++;
	}

	//copy result to initial array
	for (index = first; index <= last; ++index) {
		arr[index] = tempArr[index];
		moveCount++;
	}
	delete[] tempArr;
}

void partition(int * arr, int first, int last, int & pivotIndex, int & compCount, int & moveCount) {
	swap(arr[first], arr[last]); //so that the pivot is the last element of the array
	moveCount += 3;
	int pivot = arr[first];
	moveCount += 1;
	int lastS1 = first;
	int firstUnkown = first + 1;

	for (; firstUnkown <= last; firstUnkown++) {
		if (arr[firstUnkown] < pivot) {
			lastS1++;
			swap(arr[firstUnkown], arr[lastS1]);
			moveCount += 3;
		}
		compCount += 1;
	}
	swap(arr[first], arr[lastS1]);
	pivotIndex = lastS1;
	moveCount += 3;

}

void swap(int & x, int & y) {
	int temp = x;
	x = y;
	y = temp;
}

void insertionSort(int * arr, int first, int last, int & compCount, int & moveCount) {
	for (int unsorted = 1; unsorted <= last; unsorted++) {
		int nextItem = arr[unsorted];
		int location = unsorted;
		moveCount += 1;

		for (; location > 0 && arr[location - 1] > nextItem; location--) {
			arr[location] = arr[location - 1];
			moveCount++;
			compCount++;
		}
		arr[location] = nextItem;
		moveCount++;
		if (location > 0 ) compCount++; //count compCount only if executed
	 }
}

void mergeSort(int * arr, int first, int last, int & compCount, int & moveCount) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(arr, first, mid, compCount, moveCount);
		mergeSort(arr, mid + 1, last, compCount, moveCount);
		merge(arr, first, mid, last, compCount,	moveCount);
	}
}

void quickSort(int * arr, int first, int last, int & compCount, int & moveCount) {
	int pivotIndex;

	if (first < last) {
		partition(arr, first, last, pivotIndex, compCount, moveCount);
		quickSort(arr, first, pivotIndex - 1, compCount, moveCount);
		quickSort(arr, pivotIndex + 1, last, compCount, moveCount);
	}
}

void hybridSort(int * arr, int first, int last, int & compCount, int & moveCount) {
	int pivotIndex;
	if (first < last) {
		if (last - first <= 10) //checks if array size is less than 10
			insertionSort(arr, first, last, compCount, moveCount);
		else {
			partition(arr, first, last, pivotIndex, compCount, moveCount);
			hybridSort(arr, first, pivotIndex - 1, compCount, moveCount);
			hybridSort(arr, pivotIndex + 1, last, compCount, moveCount);
		}
	}
}

void performanceAnalysis(int size) { //long implimentation to output the whole table
	int * arr1 = new int[size];
	int * arr2 = new int[size];
	int * arr3 = new int[size];
	int * arr4 = new int[size];

	for (int i = 0; i < size; i++) //random array
		arr1[i] = arr2[i] = arr3[i] = arr4[i] = rand();

	cout << "Performance analysis for arrays of size " << size << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Random integers   Elapsed time      compCount        moveCount" << endl;

	//for insertion sort
	double duration;

	int compCount = 0;
	int moveCount = 0;

	clock_t startTime1 = clock();
	insertionSort(arr1, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Insertion sort      " << duration << "              " << compCount << "           " << moveCount << endl;

	//for Merge sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	mergeSort(arr2, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Merge sort          " << duration << "              " << compCount << "           " << moveCount << endl;

	//for quick sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	quickSort(arr3, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
    cout << "Quick sort          " << duration << "              " << compCount << "           " << moveCount << endl;

	//for hybrid sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	hybridSort(arr4, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Hybrid sort         " << duration << "              " << compCount << "           " << moveCount << endl;
	cout << "-------------------------------------------------------------" << endl;
	
	//arrays are now in ascending order
	cout << "Ascending integers   Elapsed time      compCount        moveCount" << endl;

	//insertion sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	insertionSort(arr1, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Insertion sort      " << duration << "              " << compCount << "           " << moveCount << endl;
	 
	//Merge Sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	mergeSort(arr2, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Merge sort          " << duration << "              " << compCount << "           " << moveCount << endl;
	
	//for quick sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	quickSort(arr3, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Quick sort          " << duration << "              " << compCount << "           " << moveCount << endl;

	//for hybrid sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	hybridSort(arr4, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Hybrid sort         " << duration << "              " << compCount << "           " << moveCount << endl;
	cout << "-------------------------------------------------------------" << endl;

	//Descending order array
	for (int i = 0; i < size; i++) //reverse the array
		arr1[i] = arr2[size - 1 - i];
	for (int i = 0; i < size; i++)
		arr2[i] = arr3[i] = arr4[i] = arr1[i];

	cout << "Descending integers   Elapsed time      compCount        moveCount" << endl;

	//insertion sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	insertionSort(arr1, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Insertion sort      " << duration << "              " << compCount << "           " << moveCount << endl;

	//Merge Sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	mergeSort(arr2, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Merge sort          " << duration << "              " << compCount << "           " << moveCount << endl;

	//for quick sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	quickSort(arr3, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Quick sort          " << duration << "              " << compCount << "           " << moveCount << endl;

	//for hybrid sort
	duration = 0;

	compCount = 0;
	moveCount = 0;

	startTime1 = clock();
	hybridSort(arr4, 0, size - 1, compCount, moveCount);
	duration = (clock() - startTime1) / (CLOCKS_PER_SEC / 1000.0);
	cout << "Hybrid sort         " << duration << "              " << compCount << "           " << moveCount << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
}
