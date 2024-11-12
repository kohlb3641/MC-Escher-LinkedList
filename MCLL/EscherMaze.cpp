// Brendt Kohl, Connor Simon
using namespace std;
#include "gameboard.h"
#include <iostream>

// method declarations
int main()
{
	gameboard game{15}; // set starting moves
	char dir;

	// welcome player to the game 
	cout << "Welcome user to the maze! You have fallen down a hole in the ground and end up in complete darkness." << endl
		<< "You must rely on your trusty compass to find the exit." << endl
		<< "But as a horrible stroke of luck, the ceiling is starting to crumble on top of you, and you have a limited time to find the exit!" << endl;
		
	// setup game map
	game.createMap();
	// create local player variable
	player* plr = game.getPlayer();
	// create game loop
	do {


		// cout light level of current room
		switch (plr->getCurPos()->getLightLevel())
		{
		case 0:
			cout << "The room is very dark, you can hardly see anything." << endl;
			break;
		case 1:
			cout << "The room is slightly brighter than complete darkness, you might be on the right track." << endl;
			break;
		case 2:
			cout << "The room is now very bright, you must be close to the exit." << endl;
			break;
		}

		cout << ">>You have " << game.getPlayer()->getNumMoves() << " moves remaining." << endl;
		cout << "You are in room " << plr->getCurPos()->getNodeID() << ". Where would you like to go? (n,s,e,w), q to quit:";
		cin >> dir;
		bool hitGoal = game.movePlayer(dir);
		if (hitGoal)
		{
			cout << "!! Congratulations! You've found the exit in " << game.getStartingMoves() - game.getPlayer()->getNumMoves() << " moves. !!" << endl;
			break;
		}
		// seperate dialogue
		cout << "-----------------------------------------------------------" << endl;
	} while (dir != 'q' && plr->getNumMoves() > 0);
}