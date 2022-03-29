#pragma once

#ifndef AIGUN_H
#define AIGUN_H

#include "BasicFunctions.h"

class AIGun {
public:
	AIGun(SDL_Renderer* ren);
	~AIGun();

	void ShootUpdate(float angle, int x, int y);
	void Update(float deltaTime, float playerXSpeed, float playerYSpeed, vector<SDL_Rect*> collidableObjects, int* playerHealth);
	void Reload();
	void CollisionCheck(enum collisionMask);
	void Render();
	void SetTextures(char* fireTexture,char* bulletTexture);
	void SetProjectileSize(int width, int height);

	//Gun properties
	int damage = 10;
	float fireRate = 0.2f;
	float currentFireTime = 0;
	float reloadTime = 0;
	float bulletVelocity = 1950;
	bool singleFire = false;
	int currentAmmo = maxAmmo;
	int maxAmmo = 10;
	enum gunType {
		Shotgun, Rifle, Pistol
	};

	void LoadGun(int damage, float fireRate, float reloadTime, float bulletVelocity, bool singleFire, float maxAmmo, enum gunType);

	vector<bool> inUse;

	//int GetWidth();
	//int GetHeight();
private:
	//Bullet Properties
	int bulletVectorLength = 5;
	vector<float> posX, posY;
	vector<float> xSpeed, ySpeed;
	vector<float> angle;
	vector<float> bulletLife;
	vector<bool> destroyed;
	vector<float> destroyTime;
	//void DestroyEffect();		

	vector<SDL_Rect> projectileRect;
	SDL_Texture* projectileTexture;
	SDL_Texture* destroyTexture;
	SDL_Renderer* ren;

	//Sounds* sounds;
};

#endif