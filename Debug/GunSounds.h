#pragma once
#ifndef GUNSOUNDS_H
#define GUNSOUNDS_H

#include "BasicFunctions.h"

class Sounds {
public:
	Sounds();
	~Sounds();
	void Play(char *name);
private:
	Mix_Chunk *snd_start;
	Mix_Chunk *snd_shoot;
	Mix_Chunk *snd_shoot2;
	Mix_Chunk *snd_hit;
};


#endif