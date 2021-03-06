#pragma once

void insertionSort(int *arr, int first, int last, int &compCount, int &moveCount);
void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount);
void quickSort(int *arr, int first, int last, int &compCount, int &moveCount);
void hybridSort(int *arr, int first, int last, int &compCount, int &moveCount);
void performanceAnalysis(int size);

void merge(int * arr, int first, int mid, int last, int & compCount, int &moveCount);
void partition(int * arr, int first, int last, int & pivotIndex, int & compCount, int & moveCount);
void swap(int & x, int & y);
