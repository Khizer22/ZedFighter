#include "stdafx.h"
#include "Menu.h"

Menu::Menu(SDL_Renderer* _ren) {
	ren = _ren;
	bgMoveSpeed = 15;
	bgPosX = 0;
	bgPosY = 0;
	CreateMenu();

}

Menu::~Menu() {
	//Destroy all text textures
	
	for (int i = 0; i < menuTextures.size(); i++) {
		if (menuTextures.at(i) != NULL)
			SDL_DestroyTexture(menuTextures.at(i));
	}

	//Destroy background texture
	SDL_DestroyTexture(menuBG_Texture);
	
}

//INITIALIZE MENU RECTS/TEXTURES
void Menu::CreateMenu() {
	menuRects = { {},{},{} };

	menuRects.at(0) = { 0,0,500,500 };
	menuRects.at(1) = { 0,600,500,500 };
	menuRects.at(2) = { 0,600,500,500 };

	//Create two empty textures
	menuTextures = { {},{},{} };

	//Menu Colors
	menuColors = { {},{},{} };
	menuColors.at(0) = { 200, 150, 150 };
	menuColors.at(1) = { 200, 200, 255 };
	menuColors.at(2) = { 200, 200, 255 };

	CreateFont(ren, menuTextures.at(0), &menuRects.at(0), "ZED Fighter", SCREENWIDTH / 2 - 150, SCREENHEIGHT / 2 - 200, 300, 100, menuColors.at(0));
	CreateFont(ren, menuTextures.at(1), &menuRects.at(1), "Start Game", SCREENWIDTH / 2 - 150, SCREENHEIGHT / 2 , 200, 75, menuColors.at(1));
	CreateFont(ren, menuTextures.at(2), &menuRects.at(2), "Exit Game", SCREENWIDTH / 2 - 150, SCREENHEIGHT / 2 + 100, 200, 75, menuColors.at(2));

	//Create Backgroudn and cosmestics
	menuBG_Rect = { 0,0,3000,1500 };
	menuBG_Texture = IMG_LoadTexture(ren, "Images/SpaceBG.png");
}

void Menu::Render() {
	//Render Background and cosmetics
	SDL_RenderCopy(ren, menuBG_Texture, NULL, &menuBG_Rect);

	//Render Text
	for (int i = 0; i < menuRects.size(); i++) {
		SDL_RenderCopy(ren, menuTextures.at(i), NULL, &menuRects.at(i));
	}
}

void Menu::Update(float deltaTime) {
	bgPosX -= bgMoveSpeed * deltaTime;
	if (bgPosX < -menuBG_Rect.w + SCREENWIDTH) {
		bgMoveSpeed = -bgMoveSpeed;
		bgPosX = -menuBG_Rect.w + SCREENWIDTH + 1;
	}
	else if (bgPosX > -1) {
		bgMoveSpeed = -bgMoveSpeed;
		bgPosX = 0;
	}

	menuBG_Rect.x = bgPosX;

	Render();
}

//Mouse Over Events
int Menu::HandleEvent(SDL_Event &event) {
	int mouseX = 0;
	int mouseY = 0;

	SDL_GetMouseState(&mouseX, &mouseY);

	//Mouse Over Events
	if (mouseX > menuRects.at(1).x && mouseX < menuRects.at(1).x + menuRects.at(1).w &&
		mouseY > menuRects.at(1).y && mouseY < menuRects.at(1).y + menuRects.at(1).h
		){
		SDL_SetTextureColorMod(menuTextures.at(1), 100, 50, 255);
	}
	else 
		SDL_SetTextureColorMod(menuTextures.at(1), 200, 200, 255);

	if (mouseX > menuRects.at(2).x && mouseX < menuRects.at(2).x + menuRects.at(2).w &&
		mouseY > menuRects.at(2).y && mouseY < menuRects.at(2).y + menuRects.at(2).h
		) {
		SDL_SetTextureColorMod(menuTextures.at(2), 100, 50, 255);
	}
	else
		SDL_SetTextureColorMod(menuTextures.at(2), 200, 200, 255);
	
	//Mouse Click Events
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {

		case SDL_BUTTON_LEFT:
			//SDL_GetMouseState(&mouseX, &mouseY);

			if (mouseX > menuRects.at(1).x && mouseX < menuRects.at(1).x + menuRects.at(1).w &&
				mouseY > menuRects.at(1).y && mouseY < menuRects.at(1).y + menuRects.at(1).h
				) {
				StartGame();
				return 1;
			}
			else if (mouseX > menuRects.at(2).x && mouseX < menuRects.at(2).x + menuRects.at(2).w &&
				mouseY > menuRects.at(2).y && mouseY < menuRects.at(2).y + menuRects.at(2).h
				)
			{
				return 2;
			}

			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}

bool Menu::StartGame() {
	return true;
}
