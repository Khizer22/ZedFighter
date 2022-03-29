#pragma once

#ifndef PROPS_H
#define PROPS_H

#include "BasicFunctions.h"

class Props {
public:
	Props(SDL_Renderer* ren);
	~Props();

	void SpawnProp(int spawnX, int spawnY,int width,int height,char* filePath);
	void SpawnTriggerProp(int spawnX, int spawnY, int width, int height, char* filePath);
	void ClearAllProps();

	void UpdateAllProps(float playerXSpeed, float playerYSpeed);

	vector<SDL_Rect> propRects;
private:
	void RenderPropsOnScreen();

	vector <float> posX;
	vector <float> posY;
	vector <float> posXTrigger;
	vector <float> posYTrigger;

	SDL_Renderer* ren;
	vector<SDL_Texture*> propTextures;
	vector<SDL_Texture*> propTriggerTextures;
	vector<SDL_Rect> propTriggerRects;
};

#endif