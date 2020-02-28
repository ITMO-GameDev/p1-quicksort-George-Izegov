#pragma once
#include <iostream>

template <typename T>
class Array final
{
public:
	Array();
	Array(int capacity);
	~Array();
	void insert(const T& value);
	void insert(int index, const T& value);
	void print();
	void remove(int index);
	T& operator[](int index);
	Array& operator=(Array& o);
	int size() const;

	class Iterator
	{
		friend class Array;
	public:
		Iterator();
		const T& get() const;
		void set(const T& value);
		void insert(const T& value);
		void remove();
		void next();
		void prev();
		void toIndex(int index);
		bool hasNext() const;
		bool hasPrev() const;
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
		T tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}

};

template <typename T>
Array<T>::Array()
{
	arr = new T[16];
	sizeNum = 0;
	capacity = 16;
	it.getArray(this);
}

template <typename T>
Array<T>::Array(int capacity)
{
	arr = new T[capacity];
	sizeNum = 0;
	Array::capacity = capacity;
	it.getArray(this);
}

template <typename T>
Array<T>::~Array()
{
	delete[] arr;
}

template <typename T>
void Array<T>::insert(const T& value)
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

template <typename T>
void Array<T>::insert(int index, const T& value)
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

template <typename T>
void Array<T>::print()
{
	for (int i = 0; i < sizeNum; i++)
	{
		std::cout << *(arr + i) << " ";
	}

	std::cout << std::endl;
}

template <typename T>
void Array<T>::remove(int index)
{
	for (int i = index; i < sizeNum; i++)
	{
		swap(*(arr + i), *(arr + i + 1));
	}
	sizeNum--;
}

template <typename T>
T& Array<T>::operator[](int index)
{
	return *(arr + index);
}

template <typename T>
Array<T>& Array<T>::operator=(Array& o)
{
	delete[] arr;

	sizeNum = o.sizeNum;
	capacity = o.capacity;

	T* newArr = new T[capacity];
	for (int i = 0; i < sizeNum; i++)
	{
		*(newArr + i) = *(o.arr + i);
	}
	arr = newArr;
	return *this;
}

template <typename T>
int Array<T>::size() const
{
	return sizeNum;
}

template <typename T>
Array<T>::Iterator::Iterator()
{
	curIndex = 0;
}

template <typename T>
const T& Array<T>::Iterator::get() const
{
	return *(a->arr + curIndex);
}

template <typename T>
void Array<T>::Iterator::set(const T& value)
{
	*(a->arr + curIndex) = value;
}

template <typename T>
void Array<T>::Iterator::insert(const T& value)
{
	a->insert(curIndex, value);
}

template <typename T>
void Array<T>::Iterator::remove()
{
	a->remove(curIndex);
}

template <typename T>
void Array<T>::Iterator::next()
{
	curIndex++;
}

template <typename T>
void Array<T>::Iterator::prev()
{
	curIndex--;
}

template <typename T>
void Array<T>::Iterator::toIndex(int index)
{
	curIndex = index;
}

template <typename T>
bool Array<T>::Iterator::hasNext() const
{
	return (a->size() > curIndex);
}

template <typename T>
bool Array<T>::Iterator::hasPrev() const
{
	return curIndex > 0;
}