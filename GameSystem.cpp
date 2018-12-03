#include "GameSystem.h"
#include <iostream>
#include <conio.h>
using namespace std;

//constructor sets up the game
GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);



	_level.loadLevel(levelFileName, _player);
	_level.print();
	system("PAUSE");
}


void GameSystem::playGame()
{
	bool isDone = false;

	while (isDone != true) 
	{
		_level.print();
		cout << "Health: " << _player.getHealth() << endl;
		cout << "Coins: " << _player.getCoins() << endl;

		playerMove();
		
		_level.updateEnemies(_player);
	}

}
void GameSystem::playerMove()
{
	char input;
	cout << "Press 'p' to save current game, 'q' to quit " << endl;
	input = _getch();
	if (input == 'p')
	{
		_level.saveGame(input, _player);
	}
	_level.MovePlayer(input, _player);
}
