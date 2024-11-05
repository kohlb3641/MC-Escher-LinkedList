// Brendt Kohl, Connor Simon
using namespace std;
#include "gameboard.h"
#include <iostream>
#include <fstream>

// method declarations
int main()
{
	gameboard game;
	char dir;

	// setup game map
	game.createMap();
	// create local player variable
	player* plr = game.getPlayer();
	// create game loop
	do {
		cout << "You have " << game.getPlayer()->getNumMoves() << " moves remaining." << endl;
		cout << "You are in room " << plr->getCurPos()->getNodeID() << ". Where would you like to go? (n,s,e,w), q to quit:";
		cin >> dir;
		bool hitGoal = game.movePlayer(dir);
		if (hitGoal)
		{
			cout << "Congratulations! You've found the end in " << 10 - game.getPlayer()->getNumMoves() << " moves." << endl;
			break;
		}
		// separate moves
		cout << "-----------------------------------------------------------" << endl;
	} while (dir != 'q' && plr->getNumMoves() > 0);
}