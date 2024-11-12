#pragma once
// Brendt Kohl, Connor Simon
#include <iostream>
#include <ctime> // for random
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
	int goalID{ 0 };
	const int startingMoves;
	
public:
	// default constructor - init moves to 15
	gameboard() : startingMoves(15) {}

	// optional constructor if the user wants a custom move amount
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
		// delete other initialized pointers
		delete plr;
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
		if(plr->getCurPos()->getNodeID() == goalID) {
			return true;
		}
		// check if player runs out of moves
		if (plr->getNumMoves() <= 0) {
			cout << "You have failed to make it out of the maze in time." << endl;
			return false;
		}
		// output description of room 
		switch (plr->getCurPos()->getNodeID()) {

			case 2:
				cout << "This room is humid compared to the rest of the maze. it smells like an old basement." << endl;
				break;
			case 3:
				cout << "This room smells of dead leaves. You hear distant sounds of birds and wildlife coming from no specific direction." << endl;
				break;
			case 4:
				cout << "Sounds of crashing ocean waves fill the room. the sound is deafening, yet the room is bone dry." << endl;
				break;
			case 5:
				cout << "This room gives off a dry desert heat. the wall and floors are hot to the touch." << endl;
				break;
			case 6:
				cout << "As you enter the room you begin to have feelings of nostalgia. Memories of childhood begin to flood your mind." << endl;
				break;
			case 9:
				cout << "The room floods with the voices of 1000 people. It's overwhelming and impossible to distinguish the words." << endl;
				break;
			case 10:
				cout << "As you enter the room you begin to hear classical music being played. the sound is distant and very faint." << endl;
				break;
			case 11:
				cout << "This room smells like a Wendy's" << endl;
				break;
			case 12:
				cout << "As you enter you hear distant sounds of child laughter and school bells. the Room smells of chalk from a chalk board." << endl;
				break;
			case 13:
				cout << "This room makes you feel uncomfortable, You feel as if you're being watched." << endl;
				break;
			case 14:
				cout << "Smells of campfire flood your nose, yet the room is empty." << endl;
				break;
			case 16:
				cout << "Nothing feels special about this room, It's normality is unsettling." << endl;
				break;
			case 17:
				cout << "This room feels some sort of mystical. It gives off an unearthly aura." << endl;
				break;
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

		
		goalID = rand() % 15 + 2;
		if (goalID == 8) { goalID++; }
		center = node1;
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

		// set light level of outside nodes
		for (int i = 0; i < 4; i++)
		{
			if (nextNode->getDirections(i) == nullptr) { continue; }
			nextNode->getDirections(i)->setLightLevel(2);
			// set light level of outside outside nodes
			for (int j = 0; j < 4; j++)
			{
				if (nextNode->getDirections(i)->getDirections(j) == nullptr) { continue; }
				nextNode->getDirections(i)->getDirections(j)->setLightLevel(1);
			}
		}

	}
};