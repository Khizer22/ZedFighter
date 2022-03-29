#pragma once

#ifndef MENU_H
#define MENU_H

#include "BasicFunctions.h"

class Menu {
public:
	Menu(SDL_Renderer* ren);
	~Menu();

	int HandleEvent(SDL_Event &event);
	void Update(float deltaTime);
	bool StartGame();
private:
	SDL_Renderer *ren;
	//Text Stuff
	vector<SDL_Rect> menuRects;
	vector<SDL_Texture*> menuTextures;
	vector<SDL_Color> menuColors;

	SDL_Rect menuBG_Rect;
	SDL_Texture* menuBG_Texture;

	float bgPosX, bgPosY;
	float bgMoveSpeed;
	int width,height;

	void CreateMenu();
	void Render();

	
};

#endif