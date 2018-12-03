#pragma once
#include <random>
#include <ctime>
using namespace std;
class Player 
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);


	int attack();
	int longRangeAttack();
	int takeDamage(int attack);
	//setters
	void setPosition(int x, int y);
	void setCoins(int c);
	void setHealth(int h) { h = _health; };



	void addExperience(int experience);
	//Getters
	void getPosition(int &x, int &y);
	int getHealth();
	int getCoins();

private:
	//Properties //has 5 inv slots
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;
	int _coins;
	//position
	int _x;
	int _y;
};
