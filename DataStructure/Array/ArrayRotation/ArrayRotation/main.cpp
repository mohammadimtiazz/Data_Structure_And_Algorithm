#include <iostream>
using namespace std;

enum ROTATION_TYPE {
	LEFT_ROTATION,
	RIGHT_ROTATION
};

void PrintArray(int *arr, unsigned int length) {
	for (unsigned int i = 0; i < length; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void RotationUsingTempArray(int *arr, unsigned int length, const int num_of_element_to_rotate, ROTATION_TYPE type) {
	//initialize an array with size
	int *temp_arr = new int[num_of_element_to_rotate];

	if (type == ROTATION_TYPE::LEFT_ROTATION) {
		//created a temp array with the number of element to shift
		for (unsigned int i = 0; i < num_of_element_to_rotate; i++) {
			temp_arr[i] = arr[i];
		}

		//Move rest of the array to left
		for (unsigned int i = num_of_element_to_rotate; i < length; i++) {
			arr[i - num_of_element_to_rotate] = arr[i];
		}

		//pass rest of the value from temp array
		for (unsigned int i = 0; i < num_of_element_to_rotate; i++) {
			arr[length - num_of_element_to_rotate + i] = temp_arr[i];
		}
	}
	else if (type == ROTATION_TYPE::RIGHT_ROTATION) {
		//created a temp array with the number of element to shift
		int index = 0;
		for (unsigned int i = length - num_of_element_to_rotate; i < length; i++) {
			temp_arr[index] = arr[i];
			index++;
		}

		//Move rest of the array to Right
		for (unsigned int i = length - 1; i >= num_of_element_to_rotate; i--) {
			arr[i] = arr[i - num_of_element_to_rotate];
		}

		for (unsigned int i = 0; i < num_of_element_to_rotate; i++) {
			arr[i] = temp_arr[i];
		}
	}
	else {
		std::cout << "UNDEFINED rotation type is selected" << std::endl;
	}

	delete[] temp_arr;
}


int main() {
	int arr[] = { 1,2,3,4,5,6,7 };
	//sizeof() -> how many bits needed to represent entire array
	unsigned int arr_length = sizeof(arr) / sizeof(arr[0]);
	std::cout << "The input Array is: " << std::endl;
	PrintArray(arr, arr_length);
	const int number_of_element_to_rotate = 2;
	std::cout << "Rotation using temporary array" << std::endl;
	std::cout << number_of_element_to_rotate << " element left rotation is applied: " << std::endl;
	RotationUsingTempArray(arr, arr_length, number_of_element_to_rotate, ROTATION_TYPE::LEFT_ROTATION);
	PrintArray(arr, arr_length);
	std::cout << number_of_element_to_rotate << " element right rotation is applied: " << std::endl;
	RotationUsingTempArray(arr, arr_length, number_of_element_to_rotate, ROTATION_TYPE::RIGHT_ROTATION);
	PrintArray(arr, arr_length);

	system("pause");
	return 0;
}