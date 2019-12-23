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
		for (unsigned int i = 0; i < (unsigned int)num_of_element_to_rotate; i++) {
			temp_arr[i] = arr[i];
		}

		//Move rest of the array to left
		for (unsigned int i = num_of_element_to_rotate; i < length; i++) {
			arr[i - num_of_element_to_rotate] = arr[i];
		}

		//pass rest of the value from temp array
		for (unsigned int i = 0; i < (unsigned int)num_of_element_to_rotate; i++) {
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
		for (unsigned int i = length - 1; i >= (unsigned int)num_of_element_to_rotate; i--) {
			arr[i] = arr[i - num_of_element_to_rotate];
		}

		for (unsigned int i = 0; i < (unsigned int)num_of_element_to_rotate; i++) {
			arr[i] = temp_arr[i];
		}
	}
	else {
		std::cout << "UNDEFINED rotation type is selected" << std::endl;
	}

	delete[] temp_arr;
}

void RotateOneByOne(int *arr, unsigned int length, ROTATION_TYPE type) {
	if (type == ROTATION_TYPE::LEFT_ROTATION) {
		int temp = arr[0];
		for (unsigned int i = 0; i < length - 1; i++) {
			arr[i] = arr[i + 1];
		}
		arr[length - 1] = temp;
	}
	else if (type == ROTATION_TYPE::RIGHT_ROTATION) {
		int temp = arr[length - 1];
		for (unsigned int i = length - 1; i >= 1; i--) {
			arr[i] = arr[i - 1];
		}
		arr[0] = temp;
	}
	else {
		std::cout << "UNDEFINED rotation type is selected" << std::endl;
	}

}

int GreatestCommonDivisor(int a, int b) {
	if (b == 0)
		return a;
	else
		return GreatestCommonDivisor(b, a%b);

}

//For more details of this algorithm check the following link
//https://www.geeksforgeeks.org/array-rotation/
void RotationUsingJugglingAlgorithm(int *arr, unsigned int length, const int num_of_element_to_rotate, ROTATION_TYPE type) {
	unsigned int gcd = GreatestCommonDivisor(length, num_of_element_to_rotate);

	if (type == ROTATION_TYPE::LEFT_ROTATION) {
		for (unsigned int i = 0; i < gcd; i++) {
			int temp = arr[i];	//holding the value temporarily 
			unsigned int j = i;

			while (1) {
				//if j hit the last line the break the while loop
				if (j >= length)
					break;
				//if j about to hit the last change in the array then replace with the temp value
				if (j + gcd > length - 1) {
					arr[j] = temp;
				}
				else
					arr[j] = arr[j + gcd];	//else swap with gcd distance
				j = j + gcd;
			}
			//PrintArray(arr, length);	//for debugging
		}
	}
	else if (type == ROTATION_TYPE::RIGHT_ROTATION) {
		for (unsigned int i = 0; i < gcd; i++) {
			int temp = arr[length - 1 - i];	//holding the value temporarily 
			int j = length - 1 - i;

			while (1) {
				//if j hit the beginning line the break the while loop
				if (j < 0)
					break;
				//if j about to hit the last change in the array then replace with the temp value
				if ((j - (int)gcd) < 0) {
					arr[j] = temp;
				}
				else
					arr[j] = arr[j - gcd];	//else swap with gcd distance
				j = j - gcd;
			}
			//PrintArray(arr, length);	//for debugging
		}
	}
	else {
		std::cout << "UNDEFINED rotation type is selected" << std::endl;
	}

}

void ReverseArray(int *arr, unsigned int start, unsigned int end) {
	while (start < end) {
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

void RotationUsingReversalAlgorithm(int *arr, unsigned int length, const int num_of_element_to_rotate, ROTATION_TYPE type) {
	/*
	This is For Left Rotation
	Let AB are the two parts of the input array where A = arr[0..d-1] and B = arr[d..n-1]. The idea of the algorithm is :
	Reverse A to get ArB, where Ar is reverse of A.
	Reverse B to get ArBr, where Br is reverse of B.
	Reverse all to get (ArBr) r = BA.

	Right rotation is the vice versa of this method
	*/

	if (type == ROTATION_TYPE::LEFT_ROTATION) {
		ReverseArray(arr, 0, num_of_element_to_rotate - 1);
		//PrintArray(arr, length);

		ReverseArray(arr, num_of_element_to_rotate, length - 1);
		//PrintArray(arr, length);

		ReverseArray(arr, 0, length - 1);
		//PrintArray(arr, length);
	}
	else if (type == ROTATION_TYPE::RIGHT_ROTATION) {
		ReverseArray(arr, length - num_of_element_to_rotate, length-1);
		//PrintArray(arr, length);

		ReverseArray(arr, 0, length - num_of_element_to_rotate - 1);
		//PrintArray(arr, length);

		ReverseArray(arr, 0, length - 1);
		//PrintArray(arr, length);
	}else {
		std::cout << "UNDEFINED rotation type is selected" << std::endl;
	}


}

int main() {
	int arr[] = { 1,2,3,4,5,6,7 };
	//sizeof() -> how many bits needed to represent entire array
	unsigned int arr_length = sizeof(arr) / sizeof(arr[0]);

	//-------------Method - 1: Rotation using temporary array----------//
	std::cout << "The input Array is: " << std::endl;
	PrintArray(arr, arr_length);
	int number_of_element_to_rotate = 2;
	std::cout << "Rotation using temporary array" << std::endl;
	std::cout << number_of_element_to_rotate << " element left rotation is applied: " << std::endl;
	RotationUsingTempArray(arr, arr_length, number_of_element_to_rotate, ROTATION_TYPE::LEFT_ROTATION);
	PrintArray(arr, arr_length);
	std::cout << number_of_element_to_rotate << " element right rotation is applied: " << std::endl;
	RotationUsingTempArray(arr, arr_length, number_of_element_to_rotate, ROTATION_TYPE::RIGHT_ROTATION);
	PrintArray(arr, arr_length);

	//-------------Method - 2: Rotate one by one----------//
	std::cout << "The input Array is: " << std::endl;
	PrintArray(arr, arr_length);
	std::cout << "Rotate one by one" << std::endl;
	std::cout << "Left Rotation" << std::endl;
	RotateOneByOne(arr, arr_length, ROTATION_TYPE::LEFT_ROTATION);
	PrintArray(arr, arr_length);
	std::cout << "Right Rotation" << std::endl;
	RotateOneByOne(arr, arr_length, ROTATION_TYPE::RIGHT_ROTATION);
	PrintArray(arr, arr_length);

	//-------------Method - 3: Rotation using juggling algorithm----------//
	int arr_1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	arr_length = sizeof(arr_1) / sizeof(arr_1[0]);
	number_of_element_to_rotate = 3;

	std::cout << "The input Array is: " << std::endl;
	PrintArray(arr_1, arr_length);
	std::cout << "Rotate Using Juggling Algorithm" << std::endl;
	std::cout << "Left Rotation" << std::endl;
	RotationUsingJugglingAlgorithm(arr_1, arr_length, number_of_element_to_rotate, ROTATION_TYPE::LEFT_ROTATION);
	PrintArray(arr_1, arr_length);
	std::cout << "Right Rotation" << std::endl;
	RotationUsingJugglingAlgorithm(arr_1, arr_length, number_of_element_to_rotate, ROTATION_TYPE::RIGHT_ROTATION);
	PrintArray(arr_1, arr_length);

	std::cout << "The input Array is: " << std::endl;
	PrintArray(arr_1, arr_length);
	std::cout << "Rotate Using Reversal Algorithm" << std::endl;
	std::cout << "Left Rotation" << std::endl;
	RotationUsingReversalAlgorithm(arr_1, arr_length, 3, ROTATION_TYPE::LEFT_ROTATION);
	PrintArray(arr_1, arr_length);
	std::cout << "Right Rotation" << std::endl;
	RotationUsingReversalAlgorithm(arr_1, arr_length, 3, ROTATION_TYPE::RIGHT_ROTATION);
	PrintArray(arr_1, arr_length);

	system("pause");
	return 0;
}