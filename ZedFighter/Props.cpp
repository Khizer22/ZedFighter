#include "stdafx.h"
#include "Props.h"

Props::Props(SDL_Renderer* _ren) {
	ren = _ren;
}

Props::~Props() {
	
	for (int i = 0; i < propTextures.size(); i++) {
		if (propTextures.at(i) != NULL) {
			SDL_DestroyTexture(propTextures.at(i));
			propTextures.at(i) = NULL;
		}
	}

	for (int i = 0; i < propTriggerTextures.size(); i++) {
		if (propTriggerTextures.at(i) != NULL) {
			SDL_DestroyTexture(propTriggerTextures.at(i));
			propTriggerTextures.at(i) = NULL;
		}
	}
}

void Props::SpawnProp(int spawnX, int spawnY, int width, int height, char* filePath) {
	propTextures.push_back(IMG_LoadTexture(ren,filePath));
	propRects.push_back({ spawnX, spawnY, width, height });
	posX.push_back(spawnX);
	posY.push_back(spawnY);
}

void Props::SpawnTriggerProp(int spawnX, int spawnY, int width, int height, char* filePath) {
	propTriggerTextures.push_back(IMG_LoadTexture(ren, filePath));
	propTriggerRects.push_back({ spawnX, spawnY, width, height });
	posXTrigger.push_back(spawnX);
	posYTrigger.push_back(spawnY);
}

void Props::UpdateAllProps(float playerXSpeed, float playerYSpeed) {
	for (int i = 0; i < propRects.size(); i++) {
		posX.at(i) -= playerXSpeed;
		posY.at(i) -= playerYSpeed;
		
		propRects.at(i).x = posX.at(i);
		propRects.at(i).y = posY.at(i);
	}
	for (int i = 0; i < propTriggerRects.size(); i++) {
		posXTrigger.at(i) -= playerXSpeed;
		posYTrigger.at(i) -= playerYSpeed;

		propTriggerRects.at(i).x = posXTrigger.at(i);
		propTriggerRects.at(i).y = posYTrigger.at(i);
	}
	RenderPropsOnScreen();
}

void Props::RenderPropsOnScreen() {

	for (int i = 0; i < propTriggerRects.size(); i++) {

		//Render if in Screen
		if (propTriggerRects.at(i).x < SCREENWIDTH
			&& propTriggerRects.at(i).x + propTriggerRects.at(i).w > 0
			&& propTriggerRects.at(i).y + propTriggerRects.at(i).h > 0
			&& propTriggerRects.at(i).y < SCREENHEIGHT) {
			SDL_RenderCopyEx(ren, propTriggerTextures.at(i), NULL, &propTriggerRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}

	for (int i = 0; i < propRects.size(); i++) {

		//Render if in Screen
		if (propRects.at(i).x < SCREENWIDTH
			&& propRects.at(i).x + propRects.at(i).w > 0
			&& propRects.at(i).y + propRects.at(i).h > 0
			&& propRects.at(i).y < SCREENHEIGHT) {
			SDL_RenderCopyEx(ren, propTextures.at(i), NULL, &propRects.at(i), 0, NULL, SDL_FLIP_NONE);
		}
	}
}

void Props::ClearAllProps() {
	posX.clear();
	posY.clear();
	posXTrigger.clear();
	posYTrigger.clear();
	propRects.clear();
	propTriggerRects.clear();
	propTextures.clear();
	propTriggerTextures.clear();
}
