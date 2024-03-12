#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

static int GetPosition(MatrixTerm term, int num_cols);

SparseMatrix::SparseMatrix(int num_rows, int num_cols)
{
	num_rows_ = num_rows;
	num_cols_ = num_cols;
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	int i;

	capacity_ = b.capacity_;
	num_cols_ = b.num_cols_;
	num_rows_ = b.num_rows_;
	num_terms_ = b.num_terms_;
	terms_ = new MatrixTerm[capacity_];
	while (i < num_terms_)
	{
		terms_[i] = b.terms_[i];
		i++;
	}
}

SparseMatrix::~SparseMatrix()
{
	delete[] terms_;
}

void SparseMatrix::SetValue(int row, int col, float value) // row * num_row + col 값의 오름차순으로 삽입정렬하기
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장
	const int position = row * num_cols_ + col;
	int i;

	num_terms_++;
	if (num_terms_ >= capacity_)
	{
		if (capacity_ == 0)
		{
			capacity_ = 1;
			terms_ = new MatrixTerm[capacity_];
			terms_[0].row = row;
			terms_[0].col = col;
			terms_[0].value = value;
			return ;
		}
		else
			capacity_ = capacity_ * 2;
		MatrixTerm *new_terms = new MatrixTerm[capacity_];
		i = 0;
		while (i < num_terms_ -1)
		{
			new_terms[i] = terms_[i];
			i++;
		}
		delete[] terms_;
		terms_ = new_terms;
	}

	i = num_terms_ - 2;
	int i_position;
	while (i >= 0)
	{
		i_position = GetPosition(terms_[i], num_cols_);
		if (position < i_position)
		{
			terms_[i + 1] = terms_[i];
			if (i == 0)
			{
				terms_[0].col = col;
				terms_[0].row = row;
				terms_[0].value = value;
			}
		}	
		else if (position > i_position)
		{
			terms_[i + 1].col = col;
			terms_[i + 1].row = row;
			terms_[i + 1].value = value;
			break;
		}
		else // position == i_position
		{
			terms_[i].value = value;
			break;
		}
		i--;
	}
	// PrintTerms();
	// cout<<endl;
	// cout<<endl;
}

static int GetPosition(MatrixTerm term, int num_cols)
{
	return((num_cols * term.row) + term.col);
}

float SparseMatrix::GetValue(int row, int col) const // 이진 탐색으로 검색하기
{
	// TODO: key = col + num_cols * row;
	assert(row < num_rows_);
	assert(col < num_cols_);
	int left;
	int right;
	int middle;
	int mid_position;
	const int key = row * num_cols_ + col;

	left = 0;
	right = num_terms_ -1;
	if (key > GetPosition(terms_[right], num_cols_))
		return (0);
	while (left <= right)
	{
		middle = (left + right) / 2;
		mid_position = GetPosition(terms_[middle], num_cols_);
		if (key < mid_position)
			right = middle - 1;
		else if (key > mid_position)
			left = middle + 1;
		else
			return (terms_[middle].value);
	}
	return 0;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	int i;
	int tmp_row;
	int tmp_col;

	i = 0;
	while (i < num_terms_)
	{
		temp.SetValue(terms_[i].col, terms_[i].row, terms_[i].value);
		i++;
	}
	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
