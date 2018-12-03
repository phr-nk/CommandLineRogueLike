#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "GameSystem.h"
using namespace std;

atomic<double> dFreq = 0.0;

double makeNoise(double dTime)
{
	double dOutput = 1.0 * sin(dFreq * 2 * 3.14159 * dTime);
	if (dOutput > 0.0)
		return 0.1;
	else
		return -0.1;
}
void sound()
{
	//get all sound hardware
	std::vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	//create sound machine
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
	sound.SetUserFunction(makeNoise);
}


int main()
{
	bool mainMenu = true;
	std::string levelName;
	int input;
	while (mainMenu)
	{

		
cout << "                            _.--." << endl;
cout << "                        _.-'_:-'||" << endl;
cout << "                    _.-'_.-::::'||" << endl;
cout << "               _.-:'_.-::::::'  ||" << endl;
cout << "             .'`-.-:::::::'     ||" << endl;
cout << "            /.'`;|:::::::'      ||" << endl; 
cout << "           ||   ||::::::'     _.;._'-._" << endl;
cout << "           ||   ||:::::'  _.-!oo @.!-._'-." << endl;
cout << "           \'.  ||:::::.-!()oo @!()@.-'_. |" << endl;
cout << "            '.'-;|:.-'.&$@.& ()$%-'o.'\_ ||" << endl;
cout << "              `>'-.!@%()@'@_%-'_.-o _.|'||" << endl;
cout << "               ||-._'-.@.-'_.-' _.-o  |'||" << endl;
cout << "               ||=[ '-._.-\ /.-'    o  |'||" << endl;
cout << "               || '-.]=|| |'|     SC  |'||" << endl;
cout << "               ||      || |'|        _| ';" << endl;
cout << "               ||      || |'|    _.-'_.-'" << endl;
cout << "               |'-._   || |'|_.-'_.-'" << endl;
cout << "                '-._'-.|| |' `_.-'" << endl;
cout << "                    '-.||_/.-'" << endl;
		cout << "Hello Adventurer, welcome to The Shwarfington Chronicles! Treasure and glory awaits!! " << endl;
		cout << "This lousy attempt at a game was made by yours truly, Frank Lenoci." << endl;
		cout << "What would you like to do?" << endl;
		cout << "1) Start new game: " << endl;
		cout << "2) Load game: " << endl;
		cout << "3) Quit game: " << endl;
		cin >> input;
	
		
		if (input == 1)
		{
			GameSystem gameSystem("HELLO.txt");
			gameSystem.playGame();
		}
		else if(input == 2)
		{
			cout << "Enter name of save state (no spaces):  " << endl;
			cin >> levelName;
			
			GameSystem gameSystem(levelName);
			gameSystem.playGame();
		}
		else 
		{
			cout << "Thanks for playing!" << endl;
			Sleep(2000);
			mainMenu = false;
			exit(0);
			return 0;
		}

	}


}