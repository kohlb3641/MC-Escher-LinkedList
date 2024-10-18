#pragma once
// Brendt Kohl, Connor Simon

template <typename T>
class ListNode
{
private:
	// fields for each direction
	ListNode<T>* north{ nullptr };
	ListNode<T>* south{ nullptr };
	ListNode<T>* east{ nullptr };
	ListNode<T>* west{ nullptr };

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

	ListNode<T>* getNorth() { return north; }
	ListNode<T>* getSouth() { return south; }
	ListNode<T>* getEast() { return east; }
	ListNode<T>* getWest() { return west; }

	// mutators for each direction
	void setNorth(ListNode<T>* node) { this->north = node; }
	void setSouth(ListNode<T>* node) { this->south = node; }
	void setEast(ListNode<T>* node) { this->east = node; }
	void setWest(ListNode<T>* node) { this->west = node; }
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