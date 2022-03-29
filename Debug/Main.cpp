// JetFightersGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZedFighter.h"

int main(int argc, char *argv[])
{
	JetFighterGame* jetFightersGame = new JetFighterGame();
	jetFightersGame->StartGame();

	delete jetFightersGame;

	cout << endl;
	system("PAUSE");

    return 0;
}

