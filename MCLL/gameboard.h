#pragma once
// Brendt Kohl, Connor Simon
#include <iostream>
#include <string> // for room description
#include <ctime> // for randomly choosing goal
// TODO: add descriptions for nodes
// TODO: add "light level" effect to nodes close to the goal -- optional
using namespace std;

class ListNode
{
private:
	// 0 == north, 1 == south, 2 == east, 3 == west
	ListNode* directions[4];

	// field for data
	static int counter; // for incrementing nodeID
	int nodeID;//node ID
	int eventType{ 0 };
	int lightLevel{ 0 };
	bool isDeleted{ false };
	// string variable for node description
	string roomDescription;

public:

	//basic constructor
	ListNode(int eventType) : nodeID(counter)
	{
		this->eventType = eventType;
		// increment counter
		++counter;
	}

	// default constructor
	ListNode() {
		nodeID = 0;
	}

	// data getters
	bool removed() { return isDeleted; }
	int getNodeID() { return nodeID; }
	int getLightLevel() { return lightLevel; }

	// data setters
	void setData(int data) { this->nodeID = data; }
	void setDeleted(bool deleted) { this->isDeleted = deleted; }
	void setLightLevel(int level) { this->lightLevel = level; }
	void setDescription(string desc) { this->roomDescription = desc; }

	// access methods for each direction
	ListNode* getDirections(int index) { return directions[index]; }

	// set direction for given index
	void setDirections(int index, ListNode* nodeRef) { directions[index] = nodeRef; }

	// event method
	void onTraverse()
	{
		// return if not an event node
		if (eventType == 0 || isDeleted) { return; }
		
		// determine which event to play
		if (eventType == 1) // add node event
		{
			// set this east deleted to false
			directions[2]->setDeleted(false);
			// cout something
			cout << "After walking into this room, you notice a door to the East magically open." << endl;
		}
		else // 2: delete node event
		{
			this->isDeleted = true;
			cout << "You enter the room and notice that the ceiling begins to rain down ontop of you! " << endl << "Quickly find an exit!" << endl;
		}
	}
};
// init counter to 0

int ListNode::counter{ 1 };

class player
{
private:
	ListNode* curPos{ nullptr };
	int numMoves;

public:

	player(ListNode* startingPos, int moves)
	{
		this->curPos = startingPos;
		this->numMoves = moves;
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
		int selectedDir;
		switch (dir)
		{
		case 'n':
			selectedDir = 0;
			break;
		case 's':
			selectedDir = 1;
			break;
		case 'e':
			selectedDir = 2; 
			break;
		case 'w':
			selectedDir = 3;
			break;
		default:
			// no valid direction chosen, return early
			return false;
		}
		// make temp variable for next node reference
		ListNode* selectedNode = curPos->getDirections(selectedDir);
		// check if next node is null or if its been deleted, return false early.
		if (selectedNode == nullptr || selectedNode->removed()) { return false; }

		curPos = selectedNode;
		--numMoves;
		return true;
	}
};

class gameboard
{
private:
	ListNode* center{ nullptr };
	player* plr{ nullptr };
	ListNode* goal{ nullptr };
	const int startingMoves;
	
public:
	// default constructor - init moves to 15
	gameboard() : startingMoves(15) {}

	// optional constructor if the user wants a custom move number
	gameboard(int moves) : startingMoves(moves) {}

	// Destructor
	~gameboard()
	{
		// check all paths, find next highest nodeID, delete node and continue until no paths exist
		ListNode* nextNode = center;
		int curID = nextNode->getNodeID();
		while (curID <= 17)
		{
			ListNode* tempNode = nextNode;
			curID = nextNode->getNodeID();

			// find next node
			for (int i = 0; i < 4; i++)
			{
				ListNode* ProspectedNode = nextNode->getDirections(i);
				if (ProspectedNode != nullptr && ProspectedNode->getNodeID() == curID + 1)
				{
					nextNode = ProspectedNode;
				}
			}
			// no paths found, exit loop to prevent infinite looping
			if (nextNode == tempNode) { break; }
			++curID;
			// delete tempNode
			delete tempNode;
		}
	}

	// getters
	ListNode* getHeadNode() { return center; }
	player* getPlayer() { return plr; }
	int getStartingMoves() { return startingMoves; }

	// setters
	void setHeadNode(ListNode* head) { center = head; }
	void setPlayer(player* plr) { this->plr = plr; }

	bool movePlayer(char dir)
	{
		if (dir == 'q') { return false; } // return early if user quit

		bool success = plr->movePlayer(dir);

		if (success)
		{
			cout << "You have moved to room " << plr->getCurPos()->getNodeID() << endl;
		}
		else
		{
			cout << "You hit your head on a hard stone wall. It stings a little." << endl;
		}
		// check if player hit the goal, return true
		if(plr->getCurPos() == goal){
			return true;
		}
		// check if player runs out of moves
		if (plr->getNumMoves() <= 0) {
			cout << "You have failed to make it out of the maze in time." << endl;
			return false;
		}
		
		// call onTraverse method in new node
		plr->getCurPos()->onTraverse();
		return false;
	}

	void createMap()
	{
		// prevent creating the map twice
		if (center != nullptr) { return; }

		ListNode* node1 = new ListNode(0);
		ListNode* node2 = new ListNode(0);
		ListNode* node3 = new ListNode(0);
		ListNode* node4 = new ListNode(0);
		ListNode* node5 = new ListNode(0);
		ListNode* node6 = new ListNode(0);
		ListNode* node7 = new ListNode(0);
		ListNode* node8 = new ListNode(2);
		ListNode* node9 = new ListNode(0);
		ListNode* node10 = new ListNode(0);
		ListNode* node11 = new ListNode(0);
		ListNode* node12 = new ListNode(0);
		ListNode* node13 = new ListNode(0);
		ListNode* node14 = new ListNode(0);
		ListNode* node15 = new ListNode(1);
		ListNode* node16 = new ListNode(0);
		ListNode* node17 = new ListNode(0);
		
		// For node17
		node17->setDirections(0, node5);  // North -> node5
		node17->setDirections(1, node16); // South -> node16
		node17->setDirections(2, node12); // East -> node12
		node17->setDirections(3, node15); // West -> node15
		node17->setDeleted(true);        // Set node17 to deleted

		// For node16
		node16->setDirections(0, node2);  // North -> node2
		node16->setDirections(1, node15); // South -> node15
		node16->setDirections(2, node4);  // East -> node4
		node16->setDirections(3, node11); // West -> node11

		// For node15
		node15->setDirections(0, node16); // North -> node16
		node15->setDirections(1, node3);  // South -> node3
		node15->setDirections(2, node17); // East -> node17
		node15->setDirections(3, node14); // West -> node14

		// For node14
		node14->setDirections(0, nullptr); // North -> nullptr
		node14->setDirections(1, node2);   // South -> node2
		node14->setDirections(2, node15);  // East -> node15
		node14->setDirections(3, node13);  // West -> node13

		// For node13
		node13->setDirections(0, node12);  // North -> node12
		node13->setDirections(1, node1);   // South -> node1
		node13->setDirections(2, node14);  // East -> node14
		node13->setDirections(3, node9);   // West -> node9

		// For node12
		node12->setDirections(0, node1);   // North -> node1
		node12->setDirections(1, node13);  // South -> node13
		node12->setDirections(2, node11);  // East -> node11
		node12->setDirections(3, node17);  // West -> node17

		// For node11
		node11->setDirections(0, node10);  // North -> node10
		node11->setDirections(1, node12);  // South -> node12
		node11->setDirections(2, node16);  // East -> node16
		node11->setDirections(3, nullptr); // West -> nullptr

		// For node10
		node10->setDirections(0, node9);   // North -> node9
		node10->setDirections(1, node11);  // South -> node11
		node10->setDirections(2, node1);   // East -> node1
		node10->setDirections(3, nullptr); // West -> nullptr

		// For node9
		node9->setDirections(0, node4);    // North -> node4
		node9->setDirections(1, node10);   // South -> node10
		node9->setDirections(2, node13);   // East -> node13
		node9->setDirections(3, node8);    // West -> node8

		// For node8
		node8->setDirections(0, nullptr);  // North -> nullptr
		node8->setDirections(1, node9);    // South -> node9
		node8->setDirections(2, node7);    // East -> node7
		node8->setDirections(3, nullptr);  // West -> nullptr

		// For node7
		node7->setDirections(0, nullptr);  // North -> nullptr
		node7->setDirections(1, nullptr);  // South -> nullptr
		node7->setDirections(2, node6);    // East -> node6
		node7->setDirections(3, node8);    // West -> node8

		// For node6
		node6->setDirections(0, node17);   // North -> node17
		node6->setDirections(1, nullptr);  // South -> nullptr
		node6->setDirections(2, node5);    // East -> node5
		node6->setDirections(3, node7);    // West -> node7

		// For node5
		node5->setDirections(0, node4);    // North -> node4
		node5->setDirections(1, nullptr);  // South -> nullptr
		node5->setDirections(2, node17);   // East -> node17
		node5->setDirections(3, node6);    // West -> node6

		// For node4
		node4->setDirections(0, node3);    // North -> node3
		node4->setDirections(1, node5);    // South -> node5
		node4->setDirections(2, node9);    // East -> node9
		node4->setDirections(3, node16);   // West -> node16

		// For node3
		node3->setDirections(0, node15);   // North -> node15
		node3->setDirections(1, node4);    // South -> node4
		node3->setDirections(2, nullptr);  // East -> nullptr
		node3->setDirections(3, node2);    // West -> node2

		// For node2
		node2->setDirections(0, node14);   // North -> node14
		node2->setDirections(1, node16);   // South -> node16
		node2->setDirections(2, node3);    // East -> node3
		node2->setDirections(3, node1);    // West -> node1

		// For node1
		node1->setDirections(0, node13);   // North -> node13
		node1->setDirections(1, node12);   // South -> node12
		node1->setDirections(2, node2);    // East -> node2
		node1->setDirections(3, node10);   // West -> node10


		/////////////////////////////////////
		// set headNode to node1

		// create player starting at node1
		plr = new player(node1, startingMoves);
		
		// determine random goal node
		srand(time(nullptr));

		
		int goalID = rand() % 15 + 2;
		if (goalID == 8) { goalID++; }
		center = node1;
		////////////////
		ListNode* nextNode = center;
		int curID = nextNode->getNodeID();
		// find goal node from random curID
		while (goalID != curID)
		{
			// find next node
			for (int i = 0; i < 4; i++)
			{
				ListNode* ProspectedNode = nextNode->getDirections(i);
				if (ProspectedNode != nullptr && ProspectedNode->getNodeID() == curID + 1)
				{
					nextNode = ProspectedNode;
					break;
				}
			}
			// update curID
			curID = nextNode->getNodeID();
		}
		goal = nextNode;
		//////////////////
		// set light level of outside nodes
		for (int i = 0; i < 4; i++)
		{
			if (goal->getDirections(i) == nullptr) { continue; }
			goal->getDirections(i)->setLightLevel(2);
			// set light level of outside outside nodes
			for (int j = 0; j < 4; j++)
			{
				if (goal->getDirections(i)->getDirections(j) == nullptr) { continue; }
				goal->getDirections(i)->getDirections(j)->setLightLevel(1);
			}
		}

	}
};