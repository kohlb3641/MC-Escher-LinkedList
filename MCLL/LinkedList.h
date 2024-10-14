#pragma once
// Brendt Kohl, Connor Simon

template <typename T>
class ListNode
{
private:
	// fields for each direction
	ListNode<T>* up{ nullptr };
	ListNode<T>* down{ nullptr };
	ListNode<T>* left{ nullptr };
	ListNode<T>* right{ nullptr };

	// field for data
	T data;

public:

	//basic constructor
	ListNode(T data)
	{
		this->data = data;
	}

	// data methods
	T getData() { return data; }
	void setData(T data) { this->data = data; }

	// access methods for each direction

	ListNode<T>* getUp() { return up; }
	ListNode<T>* getDown() { return down; }
	ListNode<T>* getRight() { return right; }
	ListNode<T>* getLeft() { return left; }

	// mutators for each direction
	void setUp(ListNode<T>* node) { this->up = node; }
	void setDown(ListNode<T>* node) { this->down = node; }
	void setRight(ListNode<T>* node) { this->right = node; }
	void setLeft(ListNode<T>* node) { this->left = node; }
};

template <typename T>
class DDLinkedList
{
private:
	ListNode<T>* center{ nullptr };

public:
	DDLinkedList(T data) 
	{
	// create empty node
		center = new ListNode<T>{data};
	}

	// Destructor
	~DDLinkedList()
	{
		// TODO find every node and delete them
	}
};