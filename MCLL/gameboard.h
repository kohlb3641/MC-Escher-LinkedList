#pragma once
// Brendt Kohl, Connor Simon
#include <iostream>
#include <ctime>
// TODO: add add/removing nodes -- done
// TODO: add descriptions for nodes
// TODO: add "light level" effect to nodes close to the goal -- optional


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
	int eventType{ 0 };
	bool isDeleted{ false };

public:

	//basic constructor
	ListNode(bool isEventNode, int eventType) : nodeID(counter)
	{
		this->isEventNode = isEventNode;
		this->eventType = eventType;
		// increment counter
		++counter;
	}

	// default constructor
	ListNode() {
		nodeID = 0;
		isEventNode = false;
	}
	// data methods
	bool removed() { return isDeleted; }
	int getNodeID() { return nodeID; }
	void setData(int data) { this->nodeID = data; }
	void setDeleted(bool deleted) { this->isDeleted = deleted; }

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
		if (!isEventNode || isDeleted) { return; }
		
		// determine which event to play
		if (eventType == 1)
		{
			// Add node
			// set this east deleted to false
			this->east->setDeleted(false);
			// cout something
			std::cout << "After walking into this room, you notice a door to the East magically open." << std::endl;
		}
		else
		{
			// delete node
			this->isDeleted = true;
			std::cout << "You enter the room and notice that the ceiling begins to rain down ontop of you! " << std::endl << "Quickly find an exit!" << std::endl;
		}
	}
};
// init counter to 0

int ListNode::counter{ 1 };

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
			if(curPos->getNorth() == nullptr || curPos->getNorth()->removed()){
				return false;
			}

			curPos = curPos->getNorth();
			--numMoves;
			return true;
			break;
		case 's':
			if (curPos->getSouth() == nullptr || curPos->getSouth()->removed()) {
				return false;
			}

			curPos= curPos->getSouth();
			--numMoves;
			return true;
			break;
		case 'e':
			if (curPos->getEast() == nullptr || curPos->getEast()->removed()) {
				return false;
			}
			curPos = curPos->getEast();
			--numMoves;
			return true;
		break;
		case 'w':
			if (curPos->getWest() == nullptr || curPos->getWest()->removed()) {
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
	ListNode* goal{ nullptr };

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

	bool movePlayer(char dir)
	{
		if (dir == 'q') { return false; } // return early if user quit

		bool success = plr->movePlayer(dir);

		if (success)
		{
			std::cout << "You have moved to room " << plr->getCurPos()->getNodeID() << std::endl;
		}
		else
		{
			std::cout << "You hit your head on a hard stone wall. It stings a little." << std::endl;
		}
		// check if player hit the goal, return true
		cout << "goal pointer: " << goal << " this pointer: " << plr->getCurPos() << endl;
		if(plr->getCurPos() == goal){
			return true;
		}
		// check if player runs out of moves
		if (plr->getNumMoves() <= 0) {
			std::cout << "You have failed to make it out of the maze in time." << std::endl;
			return false;
		}

		
		// call onTraverse method in new node
		plr->getCurPos()->onTraverse();
		return false;
	}

	//REMOVE -- early traverse attempt
	bool traverseTest()
	{
		ListNode* nextNode = center;
		int headID = nextNode->getNodeID();
		//determine next node
		while (headID < 16)
		{
			headID = nextNode->getNodeID();
			if (nextNode->getNorth() != nullptr && nextNode->getNorth()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getNorth();
			}
			else if (nextNode->getSouth() != nullptr &&  nextNode->getSouth()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getSouth();
			}
			else if (nextNode->getEast() != nullptr && nextNode->getEast()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getEast();
			}
			else if (nextNode->getWest() != nullptr && nextNode->getWest()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getWest();
			}
			else
			{
				break;
			}
			++headID;
		}
		if (headID == 16) return true;
	}

	void createMap()
	{
		// prevent creating the map twice
		if (center != nullptr) { return; }

		// Create nodes
		ListNode* node1 = new ListNode(false, 0);
		ListNode* node2 = new ListNode(false, 0);
		ListNode* node3 = new ListNode(false, 0);
		ListNode* node4 = new ListNode(false, 0);
		ListNode* node5 = new ListNode(false, 0);
		ListNode* node6 = new ListNode(false, 0);
		ListNode* node7 = new ListNode(false, 0);
		ListNode* node8 = new ListNode(true, 2);//delete node event
		ListNode* node9 = new ListNode(false, 0);
		ListNode* node10 = new ListNode(false, 0);
		ListNode* node11 = new ListNode(false, 0);
		ListNode* node12 = new ListNode(false, 0);
		ListNode* node13 = new ListNode(false, 0);
		ListNode* node14 = new ListNode(false, 0);
		ListNode* node15 = new ListNode(true, 1);//add node event
		ListNode* node16 = new ListNode(false, 0);
		
		// random added node
		ListNode* node17 = new ListNode(false, 0);
		// Set directional pointers
		node17->setNorth(node5); // node5 E
		node17->setSouth(node16); // node6 N
		node17->setEast(node12); // node12 W
		node17->setWest(node15); // node15 E
		// set node17 to deleted
		node17->setDeleted(true);

		//for node16
		node16->setNorth(node2);
		node16->setSouth(node15);
		node16->setEast(node4);
		node16->setWest(node11);

		// For node15
		node15->setNorth(node16);
		node15->setSouth(node3);
		node15->setEast(node17);
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
		node12->setEast(node11);
		node12->setWest(node17);

		// For node11
		node11->setNorth(node10);
		node11->setSouth(node12);
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
		node8->setEast(node7);
		node8->setWest(nullptr);

		// For node7
		node7->setNorth(nullptr);
		node7->setSouth(nullptr);
		node7->setEast(node6);
		node7->setWest(node8);

		// For node6
		node6->setNorth(node17);
		node6->setSouth(nullptr);
		node6->setEast(node5);
		node6->setWest(node7);

		// For node5
		node5->setNorth(node4);
		node5->setSouth(nullptr);
		node5->setEast(node17);
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
		
		// determine random goal node
		srand(time(nullptr));
		int goalID = rand() % 16 + 2;
		if (goalID == 8) { goalID++; }
		//std::cout << "DEBUG -- GOAL NODE IS: " << goalID << std::endl;

		ListNode* nextNode = node1;
		int headID = nextNode->getNodeID();
		while (headID <= 16)
		{
			headID = nextNode->getNodeID();
			if (headID == goalID)
			{
				goal = nextNode;
				break;
			}

			if (nextNode->getNorth() != nullptr && nextNode->getNorth()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getNorth();
			}
			else if (nextNode->getSouth() != nullptr && nextNode->getSouth()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getSouth();
			}
			else if (nextNode->getEast() != nullptr && nextNode->getEast()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getEast();
			}
			else if (nextNode->getWest() != nullptr && nextNode->getWest()->getNodeID() == headID + 1)
			{
				nextNode = nextNode->getWest();
			}
			else
			{
				// if no paths exist, break loop, set goal to center
				goal = center;
				break;
			}
			++headID;
		}
		// set light level of outside nodes
		// set light level of farther outside nodes
	}
};