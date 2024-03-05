#include <iostream>
#include <random>
using namespace std;
int *create_rand_arr(int arr_size);
void print_arr(int *arr, int arr_size);

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	// Insertion Sort
	// stability는 동일한 값을 가진 두요소들의 상대적인 순서가 정렬 과정을 거쳐도 변하지 않는 특성을 말한다. 
	// 삽입정렬은 stable한 정렬이다. 
	// 값을 옮길 때 작업을 한번만 하면된다 버블소트는 tmp에 저장, a를 b로 대치, b를 tmp로 대치 3버느이 작업을 해야한다.
	// 
	{
		int arr_size;
		int *arr;
		int i;
		int sort_i;
		int temp;
		int cnt =0;

		cout << "배열의 크기를 입력하세요: ";
		cin >> arr_size;
		arr = create_rand_arr(arr_size);
		// int arr[] = {6,5,4,3,2,1};
		// arr_size = 6;
		cout << endl;
		print_arr(arr, arr_size);
		cout <<flush;
		i = 1;
		while (i < arr_size)
		{
			sort_i = i;
			temp = arr[sort_i];
			while (arr[--sort_i] > temp && sort_i >= 0)
			{
				arr[sort_i +1] = arr[sort_i];
				cnt++;
			}
			arr[sort_i +1] = temp;
			cnt++;
			i++;
		}
		cout << endl;
		print_arr(arr, arr_size);
		cout << endl;
		cout << cnt <<endl;
	}

	// Stability
}

int *create_rand_arr(int arr_size)
{
	int *arr;
	int arr_i;
	random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 100.0);

	arr = new int[arr_size];
	while (arr_i < arr_size)
	{
		arr[arr_i] = distrib(gen);
		arr_i++;
	}
	return (arr);
}

void print_arr(int *arr, int arr_size)
{
	int i;
	i = 0;
	while (i < arr_size)
	{
		cout << arr[i] << " ";
		i++;
	}
}