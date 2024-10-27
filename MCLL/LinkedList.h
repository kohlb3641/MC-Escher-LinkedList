#pragma once
// Brendt Kohl, Connor Simon

class ListNode
{
private:
	// fields for each direction
	ListNode* north{ nullptr };
	ListNode* south{ nullptr };
	ListNode* east{ nullptr };
	ListNode* west{ nullptr };

	// field for data
	int data;//node ID
	bool isEventNode;//node 15 and node 8 are event nodes

public:

	//basic constructor
	ListNode(int data, bool isEventNode)
	{
		this->data = data;
		this->isEventNode = isEventNode;

	}

	ListNode() {} // default constructor, intentionally empty
	// data methods
	int getData() { return data; }
	void setData(int data) { this->data = data; }

	// access methods for each direction

	ListNode* getNorth() { return north; }
	ListNode* getSouth() { return south; }
	ListNode* getEast() { return east; }
	ListNode* getWest() { return west; }

	// mutators for each direction
	void setNorth(ListNode* node) { this->north = node; }
	void setSouth(ListNode* node) { this->south = node; }
	void setEast(ListNode* node) { this->east = node; }
	void setWest(ListNode* node) { this->west = node; }
};


class DDLinkedList
{
private:
	ListNode* center{ nullptr };

public:
	DDLinkedList(int data) 
	{
	// create map
		center = new ListNode(1, false);
	}

	// Destructor
	~DDLinkedList()
	{
		// TODO find every node and delete them
	}

	ListNode* getHeadNode()
	{
		return center;
	}

};