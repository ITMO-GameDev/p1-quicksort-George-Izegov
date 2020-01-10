
#include "pch.h"
#include <iostream>
#include <time.h> 
#include <windows.h>
#include <ctime>



double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

template <typename T>
void Swap(T* a, T* b)
{
	T t = *a;
	*a = *b;
	*b = t;
}

template <typename T, typename Compare>
T GetMedian(T a, T b, T c, Compare comp)
{
	if (comp(b, a)) {
		if (comp(c, b)) {
			return b;
		}
		else if (comp(c, a)) {
			return c;
		}
		else {
			return a;
		}
	}
	else {
		if (comp(c, a)) {
			return a;
		}
		else if (comp(c, b)) {
			return c;
		}
		else {
			return b;
		}
	}
}


template <typename T, typename Compare>
void QuickSort(T *first, T *last, Compare comp)
{
	while (first < last)
	{
		int left = 0;
		int right = last - first;
		T midElement = *(first + (right / 2));
		T pivot = GetMedian(*first, midElement, *last, comp);

			Swap(&pivot, &midElement);

			do
			{
				while (comp(*(first + left), pivot))
				{
					left++;
				}
				while (comp(pivot, *(first + right)))
				{
					right--;
				}
				if (left <= right)
				{
					Swap(first + left, first + right);
					left++;
					right--;
				}
			} while (left <= right);

			if (left < last - first - right)
			{
				QuickSort(first, first + right, comp);
				first += left;
			}

			else
			{
				QuickSort(first + left, last, comp);
				last -= ((last - first) - right);
			}
	}
}



template <typename T, typename Compare>
void InsertionSort(T *first, T *last, Compare comp)
{
	int N = last - first + 1;
	int j;
	T key;
	for (int i = 1; i < N; i++)
	{
		key = *(first + i);
		j = i - 1;
		while (j >= 0 && comp(key, *(first + j)))
		{
			T* temp = (first + j + 1);
			*temp = *(first + j);
			j--;
		}
		T* temp = (first + j + 1);
		*temp = key;
	}
}

template <typename T, typename Compare>
void Sort(T *first, T *last, Compare comp)
{
	if (last - first < 55)
	{
		InsertionSort(first, last, comp);
	}
	else
	{
		QuickSort(first, last, comp);
	}
}


int main()
{
	const int n = 55;
	srand(time(NULL));
	int a[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 500;
	}
}

