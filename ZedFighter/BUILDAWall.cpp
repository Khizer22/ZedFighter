#include "stdafx.h"
#include "BUILDAWall.h"

Wall::Wall(SDL_Renderer* _ren) {
	ren = _ren;

	wallTexture = IMG_LoadTexture(ren, "Images/wall.png");
	wallUpTexture = IMG_LoadTexture(ren, "Images/wall2.png");
	blockTexture = IMG_LoadTexture(ren, "Images/block.png");
}

Wall::~Wall() {
	if (wallTexture != NULL) {
		SDL_DestroyTexture(wallTexture);
		wallTexture = NULL;

	}

	if (wallUpTexture != NULL) {
		SDL_DestroyTexture(wallUpTexture);
		wallUpTexture = NULL;

	}

	if (blockTexture != NULL) {
		SDL_DestroyTexture(blockTexture);
		blockTexture = NULL;

	}
	
}

void Wall::BuildCorner(int spawnX,int spawnY) {
	//For some reason I created all walls in Stack, not a good idea lel
	blockRects.push_back({spawnX,spawnY,BLOCK_WH,BLOCK_WH });
	posXBlock.push_back(spawnX);
	posYBlock.push_back(spawnY);
}

void Wall::BuildWallAndCorner(int spawnX, int spawnY, int wallAmount, int direction, bool cornerAtBothEnds) {
	if (cornerAtBothEnds == false) {
		blockRects.push_back({ spawnX,spawnY,BLOCK_WH,BLOCK_WH });
		posXBlock.push_back(spawnX);
		posYBlock.push_back(spawnY);
		if (direction == 1) {
			//Building Right
			wallRects.push_back({ spawnX + BLOCK_Wadj,spawnY,WALL_WIDTH,WALL_HEIGHT });
			posXWall.push_back(spawnX + BLOCK_Wadj);
			posYWall.push_back(spawnY);
			for (int i = 0; i < wallAmount - 1; i++) {
				wallRects.push_back({ (spawnX + BLOCK_Wadj + WALL_WIDTH) + (i * WALL_WIDTH),spawnY,WALL_WIDTH,WALL_HEIGHT });
				posXWall.push_back((spawnX + BLOCK_Wadj + WALL_WIDTH) + (i * WALL_WIDTH));
				posYWall.push_back(spawnY);
			}
		}
		else if (direction == 0)
			//Building Up
		{
			wallRects.push_back({ spawnX,spawnY - WALL_WIDTH,WALL_HEIGHT,WALL_WIDTH });
			posXWall.push_back(spawnX );
			posYWall.push_back(spawnY - WALL_WIDTH);
			for (int i = 0; i < wallAmount - 1; i++) {
				wallRects.push_back({ spawnX,(spawnY - BLOCK_Wadj - WALL_WIDTH) - (i * WALL_WIDTH),WALL_HEIGHT,WALL_WIDTH });
				posXWall.push_back(spawnX);
				posYWall.push_back((spawnY - BLOCK_Wadj - WALL_WIDTH) - (i * WALL_WIDTH));
			}
		}
		else if (direction == 4)
		{
			//Building Left
			wallRects.push_back({ spawnX - WALL_WIDTH,spawnY,WALL_WIDTH,WALL_HEIGHT });
			posXWall.push_back(spawnX - WALL_WIDTH);
			posYWall.push_back(spawnY);
			for (int i = 0; i < wallAmount - 1; i++) {
				wallRects.push_back({ (spawnX -  WALL_WIDTH) - (i * WALL_WIDTH),spawnY,WALL_WIDTH,WALL_HEIGHT });
				posXWall.push_back((spawnX - WALL_WIDTH) - (i * WALL_WIDTH));
				posYWall.push_back(spawnY);
			}
		}
	}
}

void Wall::ClearAllWalls() {
	if (posXWall.size() > 0)
		posXWall.clear();

	if (posYWall.size() > 0)
		posYWall.clear();

	if (posXBlock.size() > 0)
		posXBlock.clear();

	if (posYBlock.size() > 0)
		posYBlock.clear();

	if (wallRects.size() > 0)
		wallRects.clear();

	if (blockRects.size() > 0)
		blockRects.clear();
}

void Wall::BuildWall(int spawnX, int spawnY, int wallAmount, float direction) {}

void Wall::UpdateAllWalls(float playerXSpeed, float playerYSpeed) {
	for (int i = 0; i < wallRects.size(); i++) {

		//Update position
		posXWall.at(i) -= playerXSpeed;
		posYWall.at(i) -= playerYSpeed;

		wallRects.at(i).x = posXWall.at(i);
		wallRects.at(i).y = posYWall.at(i);

		//Render if in Screen
		if (wallRects.at(i).x < SCREENWIDTH
			&& wallRects.at(i).x + wallRects.at(i).w > 0
			&& wallRects.at(i).y + wallRects.at(i).h > 0
			&& wallRects.at(i).y < SCREENHEIGHT) {			
			if ( wallRects.at(i).w >= WALL_WIDTH)
				SDL_RenderCopyEx(ren, wallTexture, NULL, &wallRects.at(i), 0, NULL, SDL_FLIP_NONE);
			else
				SDL_RenderCopyEx(ren, wallUpTexture, NULL, &wallRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}

	for (int i = 0; i < blockRects.size(); i++) {

		//Update position
		posXBlock.at(i) -= playerXSpeed;
		posYBlock.at(i) -= playerYSpeed;
		
		blockRects.at(i).x = posXBlock.at(i);
		blockRects.at(i).y = posYBlock.at(i);

		//Render if in Screen
		if (blockRects.at(i).x < SCREENWIDTH
			&& blockRects.at(i).x + blockRects.at(i).w > 0
			&& blockRects.at(i).y + blockRects.at(i).h > 0
			&& blockRects.at(i).y < SCREENHEIGHT) {			
			SDL_RenderCopyEx(ren, blockTexture, NULL, &blockRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}
}


//HMMM Might scrap this
void Wall::RenderWallsInScreen() {
	/*
	for (int i = 0; i < wallRects.size(); i++) {
		if (wallRects.at(i).x < SCREENWIDTH
			&& wallRects.at(i).x > 0
			&& wallRects.at(i).y > 0
			&& wallRects.at(i).y < SCREENHEIGHT) {
			//Render if in Screen
			SDL_RenderCopyEx(ren, wallTexture, NULL, &wallRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}

	for (int i = 0; i < blockRects.size(); i++) {
		if (blockRects.at(i).x < SCREENWIDTH
			&& blockRects.at(i).x > 0
			&& blockRects.at(i).y > 0
			&& blockRects.at(i).y < SCREENHEIGHT) {
			//Render if in Screen
			SDL_RenderCopyEx(ren, blockTexture, NULL, &blockRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}
	*/
}

vector<float> Wall::GetAllX(){
	vector<float> naan;
	return naan;
}

vector<float> Wall::GetAllY() {
	vector<float> naan;
	return naan;
}