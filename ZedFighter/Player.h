#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Gun.h"

class Player : public Character {
public:
	Player(SDL_Renderer* ren);
	~Player();
	void HandleEvents(SDL_Event &event);

	void Shoot();
	void Update(float deltaTime, vector<SDL_Rect*> collidableObjects, vector<SDL_Rect*>enemyRects,vector<int*> enemyHealth);
	void Render();

	float xSpeed = 0, ySpeed = 0;
private:
	//input pressed
	bool leftPressed = false;
	bool rightPressed = false;
	bool upPressed = false;
	bool downPressed = false;
	bool firePressed = false;

	//Mouse values
	int mouseX = 0, mouseY = 0;
	//Cursor Sprite
	SDL_Rect cursorRect;
	SDL_Texture* cursorTexture;

	float deltaTime;

	Gun* gun;
};

#endif