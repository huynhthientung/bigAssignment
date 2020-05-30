// my_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// created on 30/05/2020 01:20PM

#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX 1e6 // adjust the maximum of the array size here 
//global variables
double a[(int)MAX];		// sort
double b[(int)MAX];		// qsort
double c[(int)MAX];		// quick_sort
double d[(int)MAX];		// heap_sort
double e[(int)MAX];		// merge_sort

double running_time_sort		= 0.0;
double running_time_qsort		= 0.0;
double running_time_quickSort	= 0.0;
double running_time_heapSort	= 0.0;
double running_time_mergeSort	= 0.0;

int n = MAX;
void createArray() // all of them will be created 
{
	for (int i = 0; i < n; i++)
	{
		a[i] = b[i] = c[i] = d[i] = e[i] = rand() + (double)rand() / RAND_MAX;
	}
}
int compare(const void* a, const void* b)
{
	return (*(double*)a - *(double*)b);
}
void swap(double& a, double& b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}

int partition(double arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low-1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;   
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
void quickSort(double arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
void heapify(double arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}
void heapSort(double arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
void merge(double a[], int left, int mid, int right)
{
	int* temp;
	int i = left;
	int j = mid + 1;

	temp = new int[right - left + 1];

	for (int k = 0; k <= right - left; k++)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			i++;
		}
		else
		{
			temp[k] = a[j];
			j++;
		}
		if (i == mid + 1)
		{
			while (j <= right)
			{
				k++;
				temp[k] = a[j];
				j++;
			}
			break;
		}
		if (j == right + 1)
		{
			while (i <= mid)
			{
				k++;
				temp[k] = a[i];
				i++;
			}
			break;
		}
	}

	for (int k = 0; k <= right - left; k++)
		a[left + k] = temp[k];
	delete temp;
}


void mergeSort(double a[], int left, int right)
{
	if (right > left)
	{
		int mid = left + (right - left) / 2; // avoid overflow
		mergeSort(a, left, mid);
		mergeSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}
void sorted()
{
	for (int i = 0; i < n; i++)
	{
		b[i] = a[i];
		c[i] = a[i];
		d[i] = a[i];
		e[i] = a[i];
	}
}
void compare_running_time()
{
	cout << "Creating datasets...";
	cout << "\nSorting datasets...";
	printf("\n|=======================================================================================================|\n");
	printf("|\tDataset\t\t|\tsort\t|\tqsort\t|\tQuick\t|\tHeap\t|\tMerge\t|");
	printf("\n|=======================================================================================================|\n");
	int i = 0; 
	while (i < 15)
	{
		clock_t begin, end;
		createArray();
		// SORT
		begin = clock();
		sort(a, a + n);
		end = clock();
		running_time_sort = (double)(end - begin) / CLOCKS_PER_SEC;
		// QSORT
		begin = clock();
		qsort(b, n, sizeof(double), compare);
		end = clock();
		running_time_qsort = (double)(end - begin) / CLOCKS_PER_SEC;
		//QUICK_SORT
		begin = clock();
		quickSort(c, 0, n-1);
		end = clock();
		running_time_quickSort = (double)(end - begin) / CLOCKS_PER_SEC;
		// HEAP_SORT
		begin = clock();
		heapSort(d, n);
		end = clock();
		running_time_heapSort = (double)(end - begin) / CLOCKS_PER_SEC;
		// MERGE_SORT
		begin = clock();
		mergeSort(e, 0, n-1);
		end = clock();
		running_time_mergeSort = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("|\tDataset %d\t|\t%.3f\t|\t%.3f\t|\t%.3f\t|\t%.3f\t|\t%.3f\t|", 
			i + 1, running_time_sort, running_time_qsort, 
			running_time_quickSort, running_time_heapSort, running_time_mergeSort);
		printf("\n|=======================================================================================================|\n");
		i++;
	}
	sorted();
	cout << "DONE !" << endl;
}
int main()
{
	srand(time(NULL));
	compare_running_time();
	// test 
	/*cout << a[0] << " " << a[1] << " " << a[2] << endl;
	cout << b[0] << " " << b[1] << " " << b[2] << endl;
	cout << c[0] << " " << c[1] << " " << c[2] << endl;
	cout << d[0] << " " << d[1] << " " << d[2] << endl;
	cout << e[0] << " " << e[1] << " " << e[2] << endl;*/
	return 0;
}
