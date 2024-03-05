#include <iostream>
#include <random>
using namespace std;

int *create_rand_arr(int arr_size);
void print_arr(int *arr, int arr_size);
bool check_sorted(int a, int b);
int selection_sort(int *arr, int arr_size);

int main(void)
{

	int *arr;
	int arr_size;
	int arr_i;

	cout << "배열의 원소갯수를 입력하세요: ";
	cin >> arr_size;
	arr = create_rand_arr(arr_size);
	cout << "생성된 배열: ";
	print_arr(arr, arr_size);
	cout<<endl;
	cout<<endl;
	selection_sort(arr, arr_size);
	delete arr;
	return 0;
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

bool check_sorted(int a, int b)
{
	return (a <= b);
}

bool check_arr_sorted(int *arr, int arr_size)
{
	int arr_i;

	arr_i = 0;
	while(arr_i < arr_size - 1)
	{
		if (!check_sorted(arr[arr_i], arr[arr_i+1]))
		{
			cout << "arr is not sorted!" << endl;
			return false;
		}
		arr_i++;
	}
	cout << "arr is sorted!" << endl;
	return true;
}

int selection_sort(int *arr, int arr_size)
{
	int arr_i;
	int sort_i;
	int min_i;
	int tries;

	arr_i = 0;
	tries= 1;
	while (arr_i < arr_size -1)
	{
		cout << "try" << tries++ << endl;
		sort_i = arr_i;
		min_i =  sort_i++;
		while (sort_i < arr_size)
		{
			if (!check_sorted(arr[min_i],arr[sort_i]))
			{
				min_i = sort_i;
			}
			sort_i++;
		}
		swap(arr[min_i], arr[arr_i]);
		print_arr(arr, arr_size);
		if (check_arr_sorted(arr,arr_size))
			return 0;
		cout<<endl;
		cout<<endl;
		arr_i++;
	}
	return 0;
}