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

class player
{
private:
	ListNode* curPos{ nullptr };
	int numMoves;

public:

	player(ListNode* startingPos, int numMoves)
	{
		this->curPos = startingPos;
		this->numMoves = numMoves;
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
		//TODO: randomize starting node
	}

	// Destructor
	~gameboard()
	{
		// TODO find every node and delete them
	}

	ListNode* getHeadNode()
	{
		return center;
	}

	player* getPlayer()
	{
		return plr;
	}

	void setHeadNode(ListNode* head)
	{
		center = head;
	}

	void setPlayer(player* plr)
	{
		this->plr = plr;
	}
};