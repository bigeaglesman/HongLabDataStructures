#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		queue_[front_] = item;
		front_ = (capacity_ + front_ -1) % capacity_; //1개 뺴줄 때 음수가 될 수 있으므로 capacity를 1번 더해준다
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());

		rear_ = (capacity_ + rear_ -1) % capacity_;
	}

private:
	// Queue와 동일
	T *queue_ = Base::queue_;
	int &rear_ = Base::rear_;
	int &front_ = Base::front_;
	int &capacity_ = Base::capacity_;

};
