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
		cout << "You are in room " << plr->getCurPos()->getData() << ". Where would you like to go? (n,s,e,w), q to quit:";
		cin >> dir;
		game.movePlayer(dir);
		// separate moves
		cout << "-----------------------------------------------------------" << endl;
	} while (dir != 'q');
}