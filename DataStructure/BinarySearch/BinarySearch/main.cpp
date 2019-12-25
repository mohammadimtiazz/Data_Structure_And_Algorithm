#include <iostream>
using namespace std;

void PrintArray(int *arr, unsigned int length) {
	for (unsigned int i = 0; i < length; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int LinearSearch(int *arr, unsigned int length, int search_item) {

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

int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9 };
	int arr_length = sizeof(arr) / sizeof(arr[0]);
	int search_item = 6;
	int index = 0;

	cout << "The input Array: " << endl;
	PrintArray(arr, arr_length);
	index = LinearSearch(arr, arr_length, search_item);
	if (index != (-1)) {
		cout << "The number " << search_item << " found in index number " << index << endl;
	}
	else {
		cout << "the number doesn't exist in the array" << endl;
	}

	return 0;
}