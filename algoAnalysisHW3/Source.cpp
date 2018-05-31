#include <iostream>
#include <math.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

//GLOBALS
double duration;
int n = 100000;
int *seed = new int[n];
clock_t start;

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int *L = new int[n1];
	int *R = new int[n2];
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];
	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

void heapify(int arr[], int n, int i)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void printArray(int arr[], int n)
{
	for (int i = 0; i<n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

void seedWrite(int n, int seedArr[], string sName)
{
	ofstream seeds;
	seeds.open(sName + ".txt");
	for (int i = 0; i < n; i++)
	{
		seedArr[i] = seed[i];
		seeds << seedArr[i] << "\n";
	}
	seeds.close();
}
void zeroTime(string longName)
{
	cout << longName << " sort BEGIN" << endl;
	start = 0;
	start = clock();
}

void calcTime(int seedArr[], string longName, string sName)
{
	ofstream sorted;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Elapsed time: " << duration << "ms" << endl;
	sorted.open(sName + ".txt");
	for (int i = 0; i < n; i++)
		sorted << seedArr[i] << "\n";
	sorted.close();
	cout << longName << " sort END" << endl;
	sorted.close();
}

void changeElement(int seedArr[])
{
	seedArr[99999] = rand();
}

int main(void)
{
	int *seedInsertion = new int[n];
	int *seedMerge = new int[n];
	int *seedQuick = new int[n];
	int *seedHeap  = new int[n];

	//CREATE SEED
	cout << "WRITING SEED TO DISK AS TEMP ARRAYS" << endl;
	for (int i = 0; i < n; i++)
		seed[i] = rand();

	//WRITE RANDOM ARRAYS TO DISK
	string sName = "seedInsertion";
	seedWrite(n, seedInsertion, sName);
	sName = "seedMerge";
	seedWrite(n, seedMerge, sName);
	sName = "seedQuick";
	seedWrite(n, seedQuick, sName);
	sName = "seedHeap";
	seedWrite(n, seedHeap, sName);

	//SORT 'EM ALL
	string longName = "Insertation";
	sName = "sortedInsertion";
	zeroTime(longName);
	insertionSort(seedInsertion, n);
	calcTime(seedInsertion, longName, sName);

	longName = "Merge";
	sName = "sortedMerge";
	zeroTime(longName);
	mergeSort(seedMerge, 0, n - 1);
	calcTime(seedMerge, longName, sName);

	longName = "Quick";
	sName = "sortedQuick";
	zeroTime(longName);
	quickSort(seedQuick, 0, n - 1);
	calcTime(seedQuick, longName, sName);

	longName = "Heap";
	sName = "sortedHeap";
	zeroTime(longName);
	heapSort(seedHeap, n);
	calcTime(seedHeap, longName, sName);

	//SEED LIST SORTED
	ofstream sorted;
	cout << "COPYING SORTED SEED LIST" << endl;
	sorted.open("sortedSeed.txt");
	for (int i = 0; i < n; i++)
	{
		seed[i] = seedHeap[i];
		sorted << seed[i] << "\n";
	}
	sorted.close();
	cout << "COPIED" << endl;

	//Change 99999th element
	cout << "99999th element is successfully changed randomly for seed" << endl;
	cout << "Example: seed[n-1] *OLD = " << seed[n - 1] << endl;
	changeElement(seed);
	cout << "Example: seed[n-1] *NEW = " << seed[n - 1] << endl;
	
	//*NEW SEED
	sorted.open("seedNEW.txt");
	for (int i = 0; i < n; i++)
	{
		sorted << seed[i] << "\n";
	}
	sorted.close();

	//SORT 'EM ALL *NEW
	cout << "SORTING *NEW SEEDS" << endl;
	longName = "Insertation";
	sName = "sortedInsertionNEW";
	zeroTime(longName);
	insertionSort(seedInsertion, n);
	calcTime(seedInsertion, longName, sName);

	longName = "Merge";
	sName = "sortedMergeNEW";
	zeroTime(longName);
	mergeSort(seedMerge, 0, n - 1);
	calcTime(seedMerge, longName, sName);

	longName = "Quick";
	sName = "sortedQuickNEW";
	zeroTime(longName);
	quickSort(seedQuick, 0, n - 1);
	calcTime(seedQuick, longName, sName);

	longName = "Heap";
	sName = "sortedHeapNEW";
	zeroTime(longName);
	heapSort(seedHeap, n);
	calcTime(seedHeap, longName, sName);

	sorted.open("sortedSeedNEW.txt");
	for (int i = 0; i < n; i++)
	{
		seed[i] = seedHeap[i];
		sorted << seed[i] << "\n";
	}
	sorted.close();

	//REVERSE *NEW SEED
	sorted.open("reverseSeedNEW.txt");
	int big = 99999;
	for (int i = 0; i < n; i++)
	{
		seed[i] = seedHeap[big];
		sorted << seed[i] << "\n";
		--big;
	}
	sorted.close();

	//WRITE REVERSED SEEDS TO DISK
	sName = "reverseSeedInsertion";
	seedWrite(n, seedInsertion, sName);
	sName = "reverseSeedMerge";
	seedWrite(n, seedMerge, sName);
	sName = "reverseSeedQuick";
	seedWrite(n, seedQuick, sName);
	sName = "reverseSeedHeap";
	seedWrite(n, seedHeap, sName);

	//SORT 'EM ALL *NEW REVERSE
	cout << "SORTING *NEW SEEDS" << endl;
	longName = "Insertation";
	sName = "reverseSortedInsertionNEW";
	zeroTime(longName);
	insertionSort(seedInsertion, n);
	calcTime(seedInsertion, longName, sName);

	longName = "Merge";
	sName = "reverseSortedMergeNEW";
	zeroTime(longName);
	mergeSort(seedMerge, 0, n - 1);
	calcTime(seedMerge, longName, sName);

	longName = "Quick";
	sName = "reverseSortedQuickNEW";
	zeroTime(longName);
	quickSort(seedQuick, 0, n - 1);
	calcTime(seedQuick, longName, sName);

	longName = "Heap";
	sName = "reverseSortedHeapNEW";
	zeroTime(longName);
	heapSort(seedHeap, n);
	calcTime(seedHeap, longName, sName);

	sorted.open("reverseSortedSeedNEW.txt");
	for (int i = 0; i < n; i++)
	{
		seed[i] = seedHeap[i];
		sorted << seed[i] << "\n";
	}
	sorted.close();

	system("pause");
	return 0;
}