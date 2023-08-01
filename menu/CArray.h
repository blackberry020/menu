#pragma once

template <class T>
class CArray {

private:

	T* arr;
	int length;

public:

	CArray() : length(0) {
		arr = new T[1];
	}
	
	CArray(int _length) : length(_length) {
		arr = new T[_length];
	}

	CArray(T* _arr) : arr(_arr) {};

	~CArray() {
		delete[] arr;
	}

	int arrayLength() {
		return length;
	}

	T& operator[](int index) {
		if (length >= 0 && index < length) {
			return arr[index];
		}
		else {
			T* newArr = new T[index + 1];
			for (int i = 0; i < length; i++)
				newArr[i] = arr[i];
			delete[] arr;
			arr = newArr;

			for (int i = length; i < index; i++)
				arr[i] = 0;

			length = index + 1;
			return arr[index];
		}
	}

	void pushBack(T dop) {
		arr[length] = dop;
		length++;
	}

};