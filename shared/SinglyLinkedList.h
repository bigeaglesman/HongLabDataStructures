#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		Node *current;
		Node *temp;
		Node *copy_current;

		copy_current = list.first_;
		while (copy_current)
		{
			current = new Node;
			if (first_ == nullptr)
				first_ = current;
			else
				temp->next = current;
			current->item = copy_current->item;
			copy_current = copy_current->next;
			temp = current;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node *current;
		Node *temp;

		current = first_;
		while (current)
		{
			temp = current;
			current = current -> next;
			delete[] temp;
		}
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;
		Node *current;

		current = first_;
		while (current)
		{
			current = current -> next;
			size++;
		}
		return size;
	}

	T Front()
	{
		assert(first_);

		return (first_->item);
	}

	T Back()
	{
		assert(first_);
		Node *current;

		current = first_;
		while (current->next)
			current = current->next;
		return (current->item);
	}

	Node* Find(T item)
	{
		Node *current;

		current = first_;
		while (current->item != item)
		{
			current = current->next;
			if (current == nullptr)
				return nullptr;
		}

		return (current);
	}

	void InsertBack(Node* node, T item)
	{
		Node *new_node;

		new_node = new Node;
		new_node->item = item;
		new_node->next = node->next;
		node->next = new_node;
	}

	void Remove(Node* n)
	{
		assert(first_);
		Node *current;

		current = first_;
		while (current->next)
		{
			if (current->next == n)
				break;
			current = current->next;
		}
		if (current->next != n)
			return ;
		else
		{
			current->next = n->next;
			delete[] n;
		}
	}

	void PushFront(T item)
	{
		Node *new_node;
		Node *temp;

		new_node = new Node;
		new_node->item = item;
		if (first_ == nullptr)
			first_ = new_node;
		else
		{
			temp = first_;
			first_ = new_node;
			new_node->next = temp;
		}
	}

	void PushBack(T item)
	{
		Node *new_node;
		Node *back_node;
	
		new_node = new Node;
		new_node->item = item;
		if (first_)
		{
			back_node = first_;
			while (back_node->next)
				back_node = back_node->next;
			back_node->next = new_node;
		}
		else
			first_ = new_node;
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

		const Node *temp = first_;
		first_ = first_->next;
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

		Node *last_node;
		Node *second_last;
		if (first_->next)
		{
			second_last = first_;
			last_node = first_->next;
			while (last_node->next)
			{
				second_last = last_node;
				last_node = last_node->next;
			}
			delete[] last_node;
			second_last->next = nullptr;
		}
		else
		{
			delete[] first_;
			first_ = nullptr;
		}
	}

	void Reverse()
	{
		Node *temp_first;
		Node *reverse_first;

		reverse_first = nullptr;
		while (first_)
		{
			temp_first = first_->next;
			first_->next = reverse_first;
			reverse_first = first_;
			first_ = temp_first;
		}
		first_ = reverse_first;
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};