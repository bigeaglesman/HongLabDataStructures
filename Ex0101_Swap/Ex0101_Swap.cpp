#include <iostream>

using namespace std;


void MySwapPtr(int* i, int* j)
{
	int temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

void MySwapRef(int& i, int& j)
{
	i = i + j;
	j = i - j;
	i = i - j;
}

bool CheckSorted(int a, int b)
{
	return (a < b);
}

int main()
{
	// Swap
	{
		int a = 3;
		int b = 2;

		cout << a << " " << b << endl;
		MySwapRef(a,b);
		cout << a << " " << b << endl;
	}


	// 정렬(sorting)
	{
		int arr[] = { 1, 3 };
		cout << boolalpha;
		cout << arr[0] << " " << arr[1] << " " << CheckSorted(arr[0], arr[1]) << endl;
	}

	// 값과 상관 없이 항상 작은 값이 먼저 출력되게 하려면?
	// 두 값이 같을 때는 순서가 상관 없음 -> 큰 값이 먼저 출력되지 않게 하려면?
	{
		int arr[2];

		// TODO:
	}

	return 0;
}
