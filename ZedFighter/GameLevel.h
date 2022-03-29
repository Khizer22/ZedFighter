#pragma once

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include "BasicFunctions.h"
#include "BUILDAWall.h"
#include "Menu.h"
#include "EnemyGrunt.h"
#include "Props.h"

#define TILE_WIDTH 340
#define TILE_HEIGHT 340
#define TILE_AMOUNT 12
#define BOUNDRY_XMIN -500
#define BOUNDRY_XMAX 1100
#define BOUNDRY_YMIN 800
#define BOUNDRY_YMAX -1268

class GameLevel {
public:
	GameLevel(SDL_Renderer* _ren);
	~GameLevel();

	SDL_Renderer* ren;

	void CreateLevel(int level);
	void TransverseLevel(int level);
	void TransverseRound(int Round);
	void Update(float deltaTime,float playerX,float playerY);
	void HandleEventMenu(SDL_Event &event,bool &gameLoop);

	vector<SDL_Rect*> collidableObjects;
	vector<SDL_Rect*> enemyRects;
	vector<int*> enemyHealth;
	int* playerHealth;
	int round = 0;
	//Get
	int GetCurrentLevel();
private:
	SDL_Rect backgroundRect[TILE_AMOUNT];
	SDL_Texture* backgroundTex;

	float bgX[TILE_AMOUNT], bgY[TILE_AMOUNT];
	int width, height;
	int currentLevel, maxLevels;

	void Render();
	void BackgroundTileUpdate(float playerX, float playerY);

	Menu* mainMenu;

	bool tilesCreated = false;

	Wall* wallBuilder;	
	vector<Character*> enemies;
	int enemiesToSpawn = 0;

	Props* props;

	int killCount = 0;
	void RoundUpdate();

	SDL_Rect healthRect;
	SDL_Texture* healthTex;
	SDL_Rect UIHealthRect;
	SDL_Texture* UIHealthTex;


};

#endif