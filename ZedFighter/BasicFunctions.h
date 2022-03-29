#pragma once

#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H

#include <string> 
#include <time.h>
#include <vector>
#include <iostream>
#include <sstream>

#include <SDL.h>
//IMAGES
#include <SDL_image.h>
//FONTS
#include <SDL_ttf.h>
//SOUNDS
#include <SDL_mixer.h>

#include <vector>
#include <iostream>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;

static void CreateImage(SDL_Renderer* ren, SDL_Texture* &texture,SDL_Rect* rect ,int x, int y, int width, int height, char* imageToLoad) {
	texture = IMG_LoadTexture(ren, imageToLoad);
	rect->h = height;
	rect->w = width;
	rect->x = x;
	rect->y = y;

	//add collisions later 
}

static void CreateFont(SDL_Renderer* ren,SDL_Texture* &fontTexture,SDL_Rect* fontRect,char* text, int x, int y, int w, int h,SDL_Color color) {

	TTF_Font *font = TTF_OpenFont("Fonts/MyFont.ttf", 24);
	//SDL_Color color = { 120, 0, 100 };

	SDL_Surface *Surface = TTF_RenderText_Solid(font, text, color);
	fontTexture = SDL_CreateTextureFromSurface(ren, Surface);
	SDL_FreeSurface(Surface);
	TTF_CloseFont(font);

	fontRect->h = h;
	fontRect->w = w;
	fontRect->x = x;
	fontRect->y = y;
}


#endif