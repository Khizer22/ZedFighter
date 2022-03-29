#pragma once


#ifndef JETFIGHTERSGAME_H
#define JETFIGHTERSGAME_H

#include "GameLevel.h"
#include "Player.h"

class JetFighterGame {
public:
	JetFighterGame();
	~JetFighterGame();

	void StartGame();

	float deltaTime = 0;
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Rect Viewport;
	SDL_Event event;
	void InitializeSDL();
	
	bool gameLoop = true;

	//Delta Time 
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
};

#endif