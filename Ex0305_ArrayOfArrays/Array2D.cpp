#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;
// 2차원 배열은 사실 메모리상에 흩어져있는 구조이다
Array2D::Array2D(int num_rows, int num_cols)
{
	int i;
	int j;

	num_rows_ = num_rows;
	num_cols_ = num_cols;
	arrays_ = new float*[num_rows_];
	i = 0;
	while (i < num_rows_)
	{
		j = 0;
		arrays_[i] = new float[num_cols_];
		while (j < num_cols_)
		{
			SetValue(i, j, 0);
			j++;
		}
		i++;
	}
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	int i;
	int j;

	num_rows_ = b.num_rows_;
	num_cols_ = b.num_cols_;
	arrays_ = new float*[num_rows_];
	i = 0;
	while (i < num_rows_)
	{
		j = 0;
		arrays_[i] = new float[num_cols_];
		while (j < num_cols_)
		{
			SetValue(i, j, b.GetValue(i, j));
			j++;
		}
		i++;
	}
}

Array2D::~Array2D()
{
	int i;

	i = 0;
	while (i < num_rows_)
	{
		delete[] arrays_[i];
		i++;
	}
	delete[] arrays_;
}

void Array2D::SetValue(int row, int col, float value)
{
	arrays_[row][col] = value;
}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return (arrays_[row][col]);
}

Array2D Array2D::Transpose()
{
	Array2D temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Array2D temp(num_rows_, num_cols_);

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
