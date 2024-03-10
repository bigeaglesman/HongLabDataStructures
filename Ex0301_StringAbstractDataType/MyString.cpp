#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	int i;
	// 크기(size_) 결정
	size_ = strlen(init);
	// 메모리 할당
	str_ = new char[size_ + 1];
	
	// 데이터 복사
	i = 0;
	while (i < size_)
	{
		str_[i] = init[i];
		i++;
	}
	str_[i] = 0;
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	int i;
	size_ = str.size_;

	str_ = new char[size_ + 1];
	i = 0;

	while (i < size_)
	{
		str_[i] = str.str_[i];
		i++;
	}
	str_[i] = 0;
}

MyString::~MyString()
{
	// 메모리 해제
	delete[] str_;
}

bool MyString::IsEmpty()
{
	return (Length() == 0);
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	int i = 0;
	// 힌트: str.str_, str.size_ 가능
	if (size_ == str.size_)
	{
		while ((str_[i] == str.str_[i]) && i < size_)
			i++;
		if (i == size_)
			return (true);
	}
	return (false);
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	int i = 0;
	// 메모리 재할당과 원래 갖고 있던 내용 복사
	size_ = new_size;

	char *temp = new char[new_size];
	while (i < new_size)
	{
		temp[i] = str_[i];
		i++;
	}
	temp[i] = 0;
	delete[] str_;
	str_ = temp;
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	char *tmp_str;
	int 	i;
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_);

	i = 0;
	tmp_str = new char[num + 1];
	while (i < num)
	{
		tmp_str[i] = str_[start + i];
		i++;
	}
	tmp_str[i] = 0;
	return (MyString(tmp_str));
}

MyString MyString::Concat(MyString app_str)
{
	int tmp_size;
	char *tmp_str;
	int i;

	i = 0;
	tmp_size = size_ + app_str.size_ + 1;
	tmp_str = new char[tmp_size];
	while (i < size_)
	{
		tmp_str[i] = str_[i];
		i++;
	}
	while (i < tmp_size)
	{
		tmp_str[i] = app_str.str_[i - size_];
		i++;
	}
	tmp_str[i] = 0;
	return (MyString(tmp_str));
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	char *tmp_str;
	int i = 0;

	tmp_str = new char[size_ + t.size_ + 1];
	while (i < start)
	{
		tmp_str[i] = str_[i];
		i++;
	}
	while (i < start + t.size_)
	{
		tmp_str[i] = t.str_[i - start];
		i++;
	}
	while (i < size_ + t.size_)
	{
		tmp_str[i] = str_[i - t.size_];
		i++;
	}
	tmp_str[i] = 0;
	return MyString(tmp_str);
}

int MyString::Find(MyString pat)
{
	int i;
	int j;

	i = 0;
	while (str_[i])
	{
		if (str_[i] == pat.str_[0])
		{
			j = 0;
			while ((str_[i + j] == pat.str_[j]) && j < pat.size_)
				j++;
			if (j == pat.size_)
				return (i);
		}
		i++;
	}
	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}

