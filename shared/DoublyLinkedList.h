#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList()
	{
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node *current = first_;
		Node *temp;

		while (current)
		{
			temp = current;
			current = current->right;
			delete[] temp;
		}
	}

	bool IsEmpty()
	{
		if (first_)
			return (false);
		else
			return (true);
	}

	int Size()
	{
		int size = 0;
		Node *current = first_;
		
		while (current)
		{
			size++;
			current = current->right;
		}
		return size;
	}

	void Print()
	{
		using namespace std;
		Node *current = first_;
		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;
			while (current)
			{
				cout<<current->item<<" ";
				current = current->right;
			}
			cout<<endl;
		}
	}

	Node* Find(T item)
	{
		Node* current = first_;
		while (current)
		{
			if (current->item == item)
				return (current);
			current = current->right;
		}
		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		Node *new_node = new Node;
		new_node->item = item;
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			new_node->right = node->right;
			new_node->left = node;
			node->right = new_node;
			new_node->right->left = new_node;
		}
	}

	void PushFront(T item)
	{
		Node *new_node = new Node;
		new_node->item = item;
		new_node->right = first_;
		if (first_)
			first_->left = new_node;
		first_ = new_node;
	}

	void PushBack(T item)
	{
		Node *current = first_;
		Node *new_node = new Node;
		new_node->item = item;
		while(current->right)
			current = current->right;
		new_node->left = current;
		current->right = new_node;
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		Node *temp = first_;
		first_ =first_->right;
		first_->left = nullptr;
		delete[] temp;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);
		Node *current = first_;
		if (!first_->right)
		{
			delete[] current;
			first_ = nullptr;
			return ;
		}
		while (current->right->right)
			current = current->right;
		delete[] current->right;
		current->right = nullptr;
	}

	void Reverse()
	{
		Node *temp_first = first_;
		
		while (temp_first)
		{
			std::swap(temp_first->left, temp_first->right);
			first_= temp_first;
			temp_first = temp_first->left;
		}
	}

	T Front()
	{
		assert(first_);
		return (first_->item); 
	}

	T Back()
	{
		assert(first_);
		Node *current = first_;

		while (current->right)
			current = current->right;
		return (current->item);
	}

protected:
	Node* first_ = nullptr;
};