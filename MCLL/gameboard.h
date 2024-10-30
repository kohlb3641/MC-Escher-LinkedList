#pragma once
// Brendt Kohl, Connor Simon
#include <iostream>
// TODO: add add/removing nodes
// TODO: add goal node
// TODO: add "light level" effect to nodes close to the goal -- optional

// declare ListNode class
class ListNode;

int ListNode::counter{ 0 };

class ListNode
{
private:
	// fields for each direction
	ListNode* north{ nullptr };
	ListNode* south{ nullptr };
	ListNode* east{ nullptr };
	ListNode* west{ nullptr };

	// field for data
	static int counter; // for incrementing nodeID
	int nodeID;//node ID
	bool isEventNode;//node 15 and node 8 are event nodes

public:

	//basic constructor
	ListNode(bool isEventNode) : nodeID(counter)
	{
		this->isEventNode = isEventNode;

		// increment counter
		++counter;

	}

	// default constructor
	ListNode() {
		nodeID = 0;
		isEventNode = false;
	}
	// data methods
	int getData() { return nodeID; }
	void setData(int data) { this->nodeID = data; }

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

	// event method
	void onTraverse()
	{
		// return if not an event node
		if (!isEventNode) { return; }

		// destroy references to this node

		// 

		// delete this
	}
};

class player
{
private:
	ListNode* curPos{ nullptr };
	int numMoves{10};

public:

	player(ListNode* startingPos)
	{
		this->curPos = startingPos;
	}
	ListNode* getCurPos()
	{
		return curPos;
	}
	int getNumMoves()
	{
		return this->numMoves;
	}
	bool movePlayer(char dir)
	{
		switch (dir)
		{
		case 'n':
			if(curPos->getNorth() == nullptr){
				return false;
			}
			// move player

			curPos = curPos->getNorth();
			--numMoves;
			return true;
			break;
		case 's':
			if (curPos->getSouth() == nullptr) {
				return false;
			}

			curPos= curPos->getSouth();
			--numMoves;
		
			return true;
			break;
		case 'e':
			if (curPos->getEast() == nullptr) {
				return false;
			}
			curPos = curPos->getEast();
			--numMoves;
			return true;
		break;
		case 'w':
			if (curPos->getWest() == nullptr) {
				return false;
			}
			curPos = curPos->getWest();
			--numMoves;
			return true;
			break;
		default:
			return false;
		}
	}
};

class gameboard
{
private:
	ListNode* center{ nullptr };
	player* plr{ nullptr };

public:
	gameboard()
	{
		//TODO: randomize starting node (?)
	}

	// Destructor
	~gameboard()
	{
		// TODO find every node and delete them
	}

	// getters

	ListNode* getHeadNode()
	{
		return center;
	}

	player* getPlayer()
	{
		return plr;
	}

	// setters

	void setHeadNode(ListNode* head)
	{
		center = head;
	}

	void setPlayer(player* plr)
	{
		this->plr = plr;
	}

	void movePlayer(char dir)
	{
		if (dir == 'q') { return; } // return early if user quit

		bool success = plr->movePlayer(dir);

		if (success)
		{
			std::cout << "You have moved to room " << plr->getCurPos()->getData() << std::endl;
		}
		else
		{
			std::cout << "You hit your head on a hard stone wall. It stings a little." << std::endl;
		}
		
		// call onTraverse method in new node
		plr->getCurPos()->onTraverse();
	}

	void createMap()
	{
		// prevent creating the map twice
		if (center != nullptr) { return; }

		// Create nodes
		ListNode* node1 = new ListNode(false);
		ListNode* node2 = new ListNode(false);
		ListNode* node3 = new ListNode(false);
		ListNode* node4 = new ListNode(false);
		ListNode* node5 = new ListNode(false);
		ListNode* node6 = new ListNode(false);
		ListNode* node7 = new ListNode(false);
		ListNode* node8 = new ListNode(false);
		ListNode* node9 = new ListNode(false);
		ListNode* node10 = new ListNode(false);
		ListNode* node11 = new ListNode(false);
		ListNode* node12 = new ListNode(false);
		ListNode* node13 = new ListNode(false);
		ListNode* node14 = new ListNode(false);
		ListNode* node15 = new ListNode(false);
		ListNode* node16 = new ListNode(false);

		// Set directional pointers

		//for node16
		node16->setNorth(node2);
		node16->setSouth(node15);
		node16->setEast(node4);
		node16->setWest(node11);

		// For node15
		node15->setNorth(node16);
		node15->setSouth(node3);
		node15->setEast(nullptr);
		node15->setWest(node14);

		// For node14
		node14->setNorth(nullptr);
		node14->setSouth(node2);
		node14->setEast(node15);
		node14->setWest(node13);

		// For node13
		node13->setNorth(node12);
		node13->setSouth(node1);
		node13->setEast(node14);
		node13->setWest(node9);

		// For node12
		node12->setNorth(node1);
		node12->setSouth(node13);
		node12->setEast(nullptr);
		node12->setWest(nullptr);

		// For node11
		node11->setNorth(node10);
		node11->setSouth(nullptr);
		node11->setEast(node16);
		node11->setWest(nullptr);

		// For node10
		node10->setNorth(node9);
		node10->setSouth(node11);
		node10->setEast(node1);
		node10->setWest(nullptr);

		// For node9
		node9->setNorth(node4);
		node9->setSouth(node10);
		node9->setEast(node13);
		node9->setWest(node8);

		// For node8
		node8->setNorth(nullptr);
		node8->setSouth(node9);
		node8->setEast(nullptr);
		node8->setWest(nullptr);

		// For node7
		node7->setNorth(nullptr);
		node7->setSouth(nullptr);
		node7->setEast(node6);
		node7->setWest(node8);

		// For node6
		node6->setNorth(nullptr);
		node6->setSouth(nullptr);
		node6->setEast(node5);
		node6->setWest(node7);

		// For node5
		node5->setNorth(node4);
		node5->setSouth(nullptr);
		node5->setEast(nullptr);
		node5->setWest(node6);

		// For node4
		node4->setNorth(node3);
		node4->setSouth(node5);
		node4->setEast(node9);
		node4->setWest(node16);

		// For node3
		node3->setNorth(node15);
		node3->setSouth(node4);
		node3->setEast(nullptr);
		node3->setWest(node2);

		// For node2
		node2->setNorth(node14);
		node2->setSouth(node16);
		node2->setEast(node3);
		node2->setWest(node1);

		//for node1
		node1->setNorth(node13);
		node1->setSouth(node12);
		node1->setEast(node2);
		node1->setWest(node10);

		// set headNode to node1
		center = node1;

		// create player starting at node1
		plr = new player(node1);
	}
};