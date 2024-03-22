#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
	{
		K key = K();	// first
		V value = V();	// second
	};

	struct Node
	{
		Item item;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	void Preorder()
	{
		using namespace std;
		Preorder(root_);
		cout << endl;
	}

	void Preorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			cout << node->item.key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		using namespace std;
		Inorder(root_);
		cout << endl;
	}

	void Inorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			Inorder(node->left);
			cout << node->item.key << " ";
			Inorder(node->right);
		}
	}

	Item* RecurGet(const K& key)
	{
		return RecurGet(root_, key);
	}

	Item* RecurGet(Node* node, const K& key)
	{
		if (!node) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

		if (key < node->item.key)
			return RecurGet(node->left, key);
		if (key > node->item.key)
			return RecurGet(node->right, key);

		return &node->item; // if (key == node->item.key)
	}

	Item* IterGet(const K& key)
	{
		Node *current = root_;

		while(current->item.key != key)
		{
			if (current->item.key > key)
			{
				if (current->left)
					current = current->left;
				else
					return nullptr;
			}
			else if (current->item.key < key)
			{
				if (current->right)
					current = current->right;
				else
					return nullptr;
			}
		}
		return &current->item;
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << item.value << endl;
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		if (!node)
			return new Node{item, nullptr, nullptr}; // 구현 포인트 부모노드에서 널포인터 노드를 인자로 Insert함수를 사용했을 때 새로운 노드를 만들어서 그 위치에 넣는다 
		
		if (node->item.key > item.key)
			node->left = Insert(node->left, item);
		else if (node->item.key < item.key)
			node->right = Insert(node->right, item);
		else
			node->item = item;
		return (node);
	}

	void IterInsert(const Item& item)
	{
		Node *current = root_;
		Node *parent_current = nullptr;

		while (current)
		{
			parent_current = current;
			if (current->item.key > item.key)
				current = current->left;
			else if (current->item.key < item.key)
				current = current->right;
			else
			{
				current->item.value = item.value;
				return ;
			}
		}
		current = new Node {item, nullptr, nullptr};
		if (root_)
		{
			if (parent_current > item.key)
				parent_current->left = current;
			else if (parent_current < item.key)
				parent_current->right = current;
		}
		else
			root_ = current;
	}

	Node* MinKeyLeft(Node* node)
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}

	Node* Remove(Node* node, const K& key)
	{
		Node *next_node;
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			if (!node->left)
			{
				Node *temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right)
			{
				Node *temp = node->left;
				delete node;
				return temp;
			}
			Node *temp = MinKeyLeft(node->right);
			node ->item = temp->item;
			node->right = Remove(node->right, node->item.key);
		}
		return node;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (!node) return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}
