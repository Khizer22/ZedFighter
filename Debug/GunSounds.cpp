#include "stdafx.h"
#include "GunSounds.h"

Sounds::Sounds() {	
	snd_start = Mix_LoadWAV("Sounds/start.wav");
	snd_shoot = Mix_LoadWAV("Sounds/cg1.wav");
	snd_shoot2 = Mix_LoadWAV("Sounds/shoot1.wav");
	snd_hit = Mix_LoadWAV("Sounds/hit.ogg");
}
Sounds::~Sounds() {
	Mix_FreeChunk(snd_start);
	Mix_FreeChunk(snd_shoot);
	Mix_FreeChunk(snd_shoot2);
	Mix_FreeChunk(snd_hit);
	snd_start = NULL;
	snd_shoot = NULL;
	snd_shoot2 = NULL;
	snd_hit = NULL;
}

void Sounds::Play(char *name) {
	if (name == "start")
		Mix_PlayChannel(-1, snd_start, 0);
	else if (name == "shoot")
		Mix_PlayChannel(-1, snd_shoot, 0);
	else if (name == "shoot2")
		Mix_PlayChannel(-1, snd_shoot2, 0);
	else if (name == "hit")
		Mix_PlayChannel(-1, snd_hit, 0);
}

