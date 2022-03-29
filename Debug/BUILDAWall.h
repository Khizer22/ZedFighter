#pragma once

#ifndef BUILDAWALL_H
#define BUILDAWALL_H

#include "BasicFunctions.h"

#define BLOCK_WH 48
#define BLOCK_Wadj 43
#define WALL_WIDTH 225
#define WALL_HEIGHT 47

class Wall {
public:
	Wall(SDL_Renderer* ren);
	~Wall();

	void BuildWallAndCorner(int spawnX, int spawnY,int wallAmount, int direction,bool cornerAtBothEnds);
	void BuildCorner(int spawnX,int spawnY);
	void BuildWall(int spawnX, int spawnY,int wallAmount, float direction);
	void ClearAllWalls();

	void UpdateAllWalls(float playerXSpeed, float playerYSpeed);

	vector<SDL_Rect> wallRects;
	vector<SDL_Rect> blockRects;
	vector<float> GetAllX();
	vector<float> GetAllY();
private:
	void RenderWallsInScreen();

	vector <float> posXWall;
	vector <float> posYWall;
	vector <float> posXBlock;
	vector <float> posYBlock;

	SDL_Renderer* ren;
	SDL_Texture* wallTexture;
	SDL_Texture* wallUpTexture;
	SDL_Texture* blockTexture;

};

#endif