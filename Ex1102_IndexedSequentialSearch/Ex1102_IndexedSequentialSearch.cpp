#include <iostream>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

void FoundPrint(int x, int i)
{
	cout << x << " was found at " << i <<endl;
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int keys[] = { 1, 13, 55 };
	int kn = sizeof(keys) / sizeof(keys[0]);

	int indices[] = { 0, 3, 6, n }; // 마지막에 n 하나 더 추가
	int i;
	int j;
	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			i = 0;
			while (i < kn && x >= keys[i])
				i++;
			j = indices[i-1];
			while (j <= indices[i])
			{
				if (x == arr[j])
				{
					FoundPrint(x, j);
					break ;
				}
				j++;
			}
			if (j > indices[i])
				cout << x << " was not found" << endl;
		}
	}

	return 0;
}
