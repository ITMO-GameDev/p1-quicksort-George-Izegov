

#include "pch.h"
#include <iostream>

using namespace std;

template <typename T>
class Array final
{

public:
	
	Array()
	{
		arr = new T[16];
		sizeNum = 0;
		capacity = 16;
		it.getArray(this);
	}

	Array(int capacity)
	{
		arr = new T[capacity];
		sizeNum = 0;
		Array::capacity = capacity;
	}

	~Array()
	{
		delete[] arr;
	}


	void insert(const T& value)
	{
		if (sizeNum < capacity)
		{
			*(arr + sizeNum) = value;
			sizeNum++;
		}
		else
		{
			capacity *= 2;
			T* newArr = new T[capacity];
			for (int i = 0; i < sizeNum; i++)
			{
				swap(*(arr + i), *(newArr + i));
			}
			*(newArr + sizeNum) = value;
			sizeNum++;
			arr = newArr;
		}
	}

	void insert(int index, const T& value)
	{
		if (sizeNum < capacity)
		{
			for (int i = sizeNum - 1; i >= index; i--)
			{
				swap(*(arr + i), *(arr + i + 1));
			}
			*(arr + index) = value;
			sizeNum++;
		}
		else
		{
			capacity *= 2;
			T* newArr = new T[capacity];
			int j = 0;
			for (int i = 0; i < sizeNum + 1; i++)
			{
				if (i == index)
				{
					*(newArr + index) = value;
					continue;
				}
				swap(*(arr + j), *(newArr + i));
				j++;
			}
			sizeNum++;
			arr = newArr;
		}
	}

	void print()
	{
		for (int i = 0; i < sizeNum; i++)
		{
			cout << *(arr + i) << " ";
		}

		cout << endl;
	}

	void remove(int index)
	{
		for (int i = index; i < sizeNum; i++)
		{
			swap(*(arr + i), *(arr + i + 1));
		}
		sizeNum--;
	}

	T& operator[](int index)
	{
		return *(arr + index);
	}

	Array& operator=(Array& o)
	{
		delete[] arr;
	
		sizeNum = o.sizeNum;
		capacity = o.capacity;

		T* newArr = new T[capacity];
		for (int i = 0; i < sizeNum; i++)
		{
			*(newArr + i) = *(o.arr  + i);
		}
		arr = newArr;
		return *this;
	}

	int size() const
	{
		return sizeNum;
	}

	class Iterator
	{
		friend class Array;
	public:
		Iterator()
		{
			curIndex = 0;
		}

		const T& get() const
		{
			return *(a->arr + curIndex);
		}

		void set(const T& value)
		{
			*(a->arr + curIndex) = value;
		}

		void insert(const T& value)
		{
			a->insert(curIndex, value);
		}

		void remove()
		{
			a->remove(curIndex);
		}

		void next()
		{
			curIndex++;
		}

		void prev()
		{
			curIndex--;
		}

		void toIndex(int index)
		{
			curIndex = index;
		}

		bool hasNext() const
		{
			return (a->size() > curIndex);
		}

		bool hasPrev() const
		{
			return curIndex > 0;
		}

	private:
		int curIndex;
		Array* a;

		void getArray(Array* array)
		{
			a = array;
		}
	};

	Iterator iterator()
	{
		return it;
	}

private:
	int sizeNum, capacity;
	T* arr;
	Iterator it;

	void swap(T& a, T& b)
	{
		T tmp = move(a);
		a = move(b);
		b = move(tmp);
	}
};

int main()
{
}

