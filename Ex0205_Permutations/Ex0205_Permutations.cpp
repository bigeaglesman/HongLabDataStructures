#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

void RecurPermutations(char* arr, int left, int right)
{
	// arr[left], ..., arr[right]

	if (left == right)
	{
		for (int i = 0; i <= right; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	else
	{
		for (int i = left; i <= right ; i++)
		{
			swap(arr[i], arr[left]);   //바꾸고
			RecurPermutations(arr, left + 1, right); //고정한다
			swap(arr[i], arr[left]); //swap한 배열을 다시 되돌려 준다. 
		}
	}
}

int main()
{
	/* a 한 글자의 순열 (Permutations)pwd
		a
	*/

	/* ab 두 글자의 순열 (Permutations)

	*/

	/*  abc 3 글자의 순열 (Permutations)

		a b c
		a c b
		b a c
		b c a
		c b a
		c a b
	*/

	// Permutations
	char arr[] = "abcdefg";

	RecurPermutations(arr, 0, 0);
	cout << endl;

	RecurPermutations(arr, 0, 1);
	cout << endl;

	RecurPermutations(arr, 0, 2);
	cout << endl;


		RecurPermutations(arr, 0, 7);

	// RecurPermutations(arr, 0, 3);
	// cout << endl;

	return 0;
}
