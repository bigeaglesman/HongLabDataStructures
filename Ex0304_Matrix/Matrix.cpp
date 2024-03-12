#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;
// 배열은  2차원 이지만 메모리 상에는 1차원으로 존재한다
Matrix::Matrix(int num_rows, int num_cols)
{
	int i = 0;
	num_cols_ = num_cols;
	num_rows_ = num_rows;
	const int size = num_rows * num_cols;

	values_ = new float[size];
	while (i < size)
	{
		values_[i] = 0;
		i++;
	}
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	num_cols_ = b.num_cols_;
	num_rows_ = b.num_rows_;
	const int size = b.num_cols_ * b.num_rows_;
	int i = 0;

	values_ = new float[size];
	while (i < size)
	{
		values_[i] = b.values_[i];
		i++;
	}
}

Matrix::~Matrix()
{
	delete []values_;
}

void Matrix::SetValue(int row, int col, float value)
{
	values_[(row * num_cols_) + col]= value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	float value;

	value = values_[(row * num_cols_) + col];
	return value;
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의
	int row;
	int col;

	col = 0;
	while (col < num_cols_)
	{
		row = 0;
		while (row < num_rows_)
		{
			temp.SetValue(col, row, GetValue(row, col)); //멤버함수 사용해서 단순하게 구현하기
			row++;
		}
		col++;
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);

	const int size = num_cols_ * num_rows_;
	int i;

	i = 0;
	while (i < size)
	{
		temp.values_[i] = values_[i] + b.values_[i];
		i++;
	}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
