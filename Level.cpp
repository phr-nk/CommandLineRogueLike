#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>
Level::Level()
{
}


void Level::loadLevel(string fileName, Player &player)
{

	//Loads the level
	ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);

	}

	string line;

	while (getline(file, line)) 
	{
		_levelData.push_back(line);

	}
	file.close();

	//Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];

			switch (tile) 
			{
			case '@'://player
				player.setPosition(j, i);
				break;
			case 'S'://Snake
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'O':
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 40, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
				_enemies.back().setPosition(j, i);
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
				break;
			case '/': //items
				_items.push_back(Item("Sword", tile));
				_items.back().setPosition(j, i);

			}
		}
	}

}

void Level::print()
{

	std::cout << string(100, '\n');


	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());


	}
	

}

void Level::clearScreen()
{
	cout << string(25, '\n');
}

void Level::MovePlayer(char input, Player &player)
{
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);



	switch (input) {
	case 'W': //up
	case 'w':

		processPlayerMove(player, playerX, playerY - 1);

		break;
	case 'S': //down
	case 's':

		processPlayerMove(player, playerX, playerY + 1);

		break;
	case 'A': // left
	case 'a':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'D'://right
	case 'd':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	case 'q':
		exit(0);
	case'i':
		clearScreen();
		if (_inventory.size() == 0)
		{
			cout << "Inventory is empty!!" << endl;
		}
		else
		{
			for (int i = 0; i < _inventory.size(); ++i)
			{
				cout << "You have: " << _inventory[i].getName() << " " << endl;
			}
		}
	
	default:
		system("PAUSE");
	}

}

void Level::saveGame(char input, Player &player)
{
	ofstream save;
	std::string fname;
	
	if (input == 'p')
	{
		cout << "What is the name of the file you want to save to ? " << endl;
		getline(cin, fname);

		save.open(fname);
		if (save.fail())
		{
			//Convert to C-String to comply with perror function parameters.
			cout << "Error! " <<std::endl;
		
		}

		for (int i = 0; i < _levelData.size(); i++)
		{
			save << _levelData[i].c_str() << endl;

		}

		save << endl;

		save << player.getHealth() << endl;
		save << player.getCoins() << endl;

		save.close();
		cout << "Save succesful!" << endl;

	}

}

void Level::updateEnemies(Player &player) {
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;


	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++)
	{
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) 
		{
		case 'w':

			processEnemyMove(player, i, enemyX, enemyY - 1);

			break;
		case 's':

			processEnemyMove(player, i, enemyX, enemyY + 1);

			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;

		}
	}
}



char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) 
{
	_levelData[y][x] = tile;

}

void Level::processPlayerMove(Player &player, int targetX, int targetY) 
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case '/':
		viewItem(player, targetX, targetY);


	}


}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) 
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) 
	{
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	case '#':
		break;
	
	}




}
void Level::viewItem(Player & player, int targetX, int targetY)
{
	int itemX;
	int itemY;
	int playerX;
	int playerY;
	string itemName;
	char input;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _items.size(); ++i)
	{
		_items[i].getPosition(itemX, itemY);
		itemName = _items[i].getName();

		if (targetX == itemX && targetY == itemY)
		{
			cout <<endl << "You see an Item in front of you..." << endl;
			cout << "What would you like to do? " << endl;
			cout << "1) Inspect Item " << endl;
			cout << "2) Pick up Item " << endl;
			cin >> input;

			switch (input)
			{
				case'1':
					
					cout << "You get closer to the item and see that it is a " << _items[i].getName() << "! " << endl;
					system("PAUSE");
				case '2':
					setTile(targetX, targetY, '.');
					print();
					
					cout << "A " << _items[i].getName() << " has been placed in your inventory! " << endl;
					_inventory.push_back(_items[i]);
					
					system("PAUSE");

			}
		}

	}
}
void Level::battleMonster(Player &player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int attackRoll;
	int attackResult;
	int playerX;
	int playerY;
	int coins;
	char input;
	bool inBattle = false;
	string enemyName;

	player.getPosition(playerX, playerY);
	clearScreen();

	cout << "You enter a battle!" << endl;
	while (!inBattle)
	{
		cout << "What would you like to do " << endl;
		cout << "1) Fight " << endl;
		cout << "2) Use item " << endl;
		cout << "3) Run " << endl;

		cin >> input;

		clearScreen();
		switch (input)
		{

		case '1':
			for (int i = 0; i < _enemies.size(); i++)
			{
				_enemies[i].getPosition(enemyX, enemyY);
				enemyName = _enemies[i].getName();
				if (targetX == enemyX && targetY == enemyY)
				{
					cout << _enemies[i].getName() <<" Health: " << _enemies[i].getHealth() << endl;
					cout << "Player Health: " << player.getHealth() << endl;
					//battle
					attackRoll = player.attack();
					printf("\nPlayer attacked %s with a roll of: %d\n", enemyName.c_str(), attackRoll);
					attackResult = _enemies[i].takeDamage(attackRoll);
					
					if (attackResult != 0) 
					{
						setTile(targetX, targetY, '.');
						print();
						printf("Monster died!\n");
						if (_enemies[i].getName() == "Snake")
						{
							coins = 1 + rand() % 6;
							player.setCoins(coins);
							cout << "You got " << coins << " coins! " << endl;
						}

						//Remove the enemy
						_enemies[i] = _enemies.back();
						_enemies.pop_back();
						i--;
						//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
						//the same way
						system("PAUSE");
						player.addExperience(attackResult);



						return;
					}
					//Monster turn!
					attackRoll = _enemies[i].attack();
					printf("%s attacked player with a roll of: %d\n", enemyName.c_str(), attackRoll);
				
					attackResult = player.takeDamage(attackRoll);

					if (attackResult != 0) 
					{

						setTile(playerX, playerY, 'X');
						printf("You died!\n");
						print();
						//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
						//the same way
						system("PAUSE");

						exit(0);
						return;
					}
					//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
					//the same way
					system("PAUSE");

					//return;
				}
			}
		}
	}
}