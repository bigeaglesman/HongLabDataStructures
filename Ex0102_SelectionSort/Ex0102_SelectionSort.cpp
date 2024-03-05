#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

struct Element
{
	int key;
	char value;
};

bool CheckSorted(int* arr, int size)
{
	int i = 0;

	while (i < size -1)
	{
		if (arr[i] > arr[i+1])
			return false;
		i++;
	}
	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void Print(Element* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i].key << " ";
	cout << endl;

	for (int i = 0; i < size; i++)
		cout << arr[i].value << " ";
	cout << endl;
}

int main()
{
	// 3개 정렬
	{
		for (int k = 0; k < 3; k++)
			for (int j = 0; j < 3; j++)
				for (int i = 0; i < 3; i++) {

					int arr[3] = { i, j, k };
					int size = sizeof(arr) / sizeof(arr[0]);

					for (int e = 0; e < size; e++) {
						cout << arr[e] << " " << flush;
					}

					cout << boolalpha;
					cout << CheckSorted(arr, size); // 정렬 되었나 확인

					cout << " -> " << flush;

					int arr_i;
					int sort_i;
					int val;
					arr_i = 0;
					while (arr_i < size)
					{
						sort_i = arr_i;
						val = arr[sort_i++];
						while (sort_i < size)
						{
							if (val > arr[sort_i])
								swap(val, arr[sort_i]);
							sort_i++;
						}
						arr[arr_i] = val;
						arr_i++;
					}

					for (int e = 0; e < size; e++) {
						cout << arr[e] << " " << flush;
					}

					cout << boolalpha;
					cout << CheckSorted(arr, size); // 정렬 되었나 확인
					cout << endl;
				}
	}


	// // 5개라면? 더 많다면?
	// {
	// 	// 8 4 2 8 3
	// 	// TODO: ???

	// 	// 8 3 2 5 1 1 2 5 8 9
	// 	// TODO: ???

	// 	// 100개라면?
	// }

	// 가장 작은 수 찾기
	{
		int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 0 }; // 임의의 숫자들, 변경 가능
		int size = sizeof(arr) / sizeof(arr[0]);
		int min_number;

		assert(size > 0); // size가 1이상이라고 가정
		int min_i = 0;
		int i = min_i;
		min_number = arr[min_i++];
		while (min_i < size)
		{
			if (arr[min_i] < min_number)
			{
				min_number = arr[min_i];
				i = min_i;
			}
			min_i++;
		}
		cout << "Minimum number is " << min_number << " Minimum number index is " << i << endl;
	}

	return 0; // <- 실습용 임시
	// // 가장 작은 수의 인덱스 찾기
	// {
	// 	int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
	// 	int size = sizeof(arr) / sizeof(arr[0]);

	// 	assert(size > 0); // size가 1이상이라고 가정

	// 	// TODO:

	// 	//cout << "The index of min is " << min_index << endl;
	// 	//cout << "Minimum number is " << arr[min_index] << endl;
	// }

	// // Selection Sort
	// // 힌트: swap()
	// {
	// 	int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
	// 	int size = sizeof(arr) / sizeof(arr[0]);

	// 	int min_index;
	// 	for (int i = 0; i < size - 1; i++)
	// 	{

	// 		// TODO:

	// 		Print(arr, size);

	// 		cout << boolalpha;
	// 		cout << CheckSorted(arr, size);
	// 		cout << endl;
	// 	}
	// }

	// // 비교 횟수 세보기, 더 효율적인 방법은 없을까?
	// // https://en.wikipedia.org/wiki/Sorting_algorithm
	// {
	// 	ofstream ofile("log.txt");
	// 	for (int size = 1; size < 1000; size++)
	// 	{
	// 		int count = 0;
	// 		int* arr = new int[size];
	// 		for (int s = 0; s < size; s++) {
	// 			arr[s] = size - s;
	// 		}

	// 		//TODO: count ++;

	// 		//cout << size << ", " << count << endl;
	// 		ofile << size << ", " << count << endl;
	// 		// Print(arr, size);

	// 		delete[] arr;
	// 	}

	// 	ofile.close();
	// }

	// // [2, 2, 1]
	// // [1, 2, 2] // 첫 2가 마지막으로 이동

	// // 안정성 확인(unstable)
	// {
	// 	Element arr[] = { {2, 'a'}, {2, 'b'}, {1, 'c'} };
	// 	int size = sizeof(arr) / sizeof(arr[0]);

	// 	Print(arr, size); // arr이 Element의 배열

	// 	// TODO:

	// 	Print(arr, size); // arr이 Element의 배열
	// }
}
