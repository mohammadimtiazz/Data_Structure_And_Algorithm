#include <iostream>
#include <math.h>
using namespace std;

void PrintArray(int *arr, unsigned int length) {
	for (unsigned int i = 0; i < length; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int LinearSearch(int *arr, unsigned int length, int search_item) {
	/*

	Start from the leftmost element of arr[] and one by one compare x with each element of arr[]
	If x matches with an element, return the index.
	If x doesn’t match with any of elements, return -1.

	*/
	if (length <= 0) {
		return -1;
	}

	for (unsigned int i = 0; i < length; i++) {
		if (arr[i] == search_item) {
			return i;
		}
	}
	return -1;
}

int BinarySearchRecursion(int *arr, int start_index, int end_index, int search_item) {
	// (starting_index + (end_index - 1)) / 2 = shows the middle distance between two index
	// +1 added at the end to deal with floating number and it's correction
	int middle_index = ((start_index + (end_index-1)) / 2) + 1;

	//if search item found then return the index
	if (arr[middle_index] == search_item) {
		return middle_index;
	}

	//if search item is bigger then the arr[middle_index] value then move the starting index
	if (arr[middle_index] < search_item){
		return BinarySearchRecursion(arr, middle_index + 1, end_index, search_item);
	}
	else {
		//if search item is smaller then the arr[middle_index] value then move the end index
		return BinarySearchRecursion(arr, start_index, middle_index - 1, search_item);;
	}
	return -1;
}

int BinarySearch(int *arr, int starting_index, int end_index, int search_item) {
	while (starting_index <= end_index) {
		// (starting_index + (end_index - 1)) / 2 = shows the middle distance between two index
		// +1 added at the end to deal with floating number and it's correction
		int middle_index = ( (starting_index + (end_index - 1)) / 2 ) + 1;

		//if search item found then return the index
		if (arr[middle_index] == search_item) {
			return middle_index;
		}

		//if search item is bigger then the arr[middle_index] value then move the starting index
		if (arr[middle_index] < search_item) {
			starting_index = middle_index + 1;
		}
		else {
			//if search item is smaller then the arr[middle_index] value then move the end index
			end_index = middle_index - 1;
		}

	}
	return -1;
}


int main() {
	int arr[] = { 2,5,8,12,16,23,38,56,72,91 };
	int arr_length = sizeof(arr) / sizeof(arr[0]);
	int search_item = 23;
	int index = 0;

	cout << "The input Array: " << endl;
	PrintArray(arr, arr_length);
	index = LinearSearch(arr, arr_length, search_item);
	cout << "Applying Linear search algorithm" << endl;
	if (index != (-1)) {
		cout << "The number " << search_item << " found in index number " << index << endl;
	}
	else {
		cout << "the number doesn't exist in the array" << endl;
	}

	index = BinarySearch(arr, 0, arr_length -1, search_item);
	cout << "Applying Binary search algorithm" << endl;
	if (index != (-1)) {
		cout << "The number " << search_item << " found in index number " << index << endl;
	}
	else {
		cout << "the number doesn't exist in the array" << endl;
	}

	search_item = 8;
	index = BinarySearchRecursion(arr, 0, arr_length - 1, search_item);
	cout << "Applying Binary search recursion algorithm" << endl;
	if (index != (-1)) {
		cout << "The number " << search_item << " found in index number " << index << endl;
	}
	else {
		cout << "the number doesn't exist in the array" << endl;
	}

	return 0;
}