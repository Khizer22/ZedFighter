#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "BasicFunctions.h"

class Character {
public:	
	virtual ~Character();
	virtual void Update(float deltaTime, float playerXSpeed, float playerYSpeed);
	virtual void Update(float deltaTime, float playerXSpeed, float playerYSpeed, vector<SDL_Rect*>collidableObjects, int* playerHealth);
	virtual void SetStats(float maxSpeed, float maxHealth);
	virtual void SetTexture(char* newTexture);
	virtual void LoadGunAI(int _damage, float _fireRate, float _reloadTime, float _bulletVelocity, bool _singleFire, float _maxAmmo,char* fireTexture,char*bulletTexture,int bulletWidth,int bulletHeight);
	float GetX();
	float GetY();
	float GetCurrentSpeed();
	float GetMovingDirection();

	SDL_Renderer* ren;
	float posX = 0, posY = 0;
	float angle;
	int width, height;
	float currentSpeed, maxSpeed, acceleration,direction;
	int damage, maxHealth,currentHealth;
	int spawnX, spawnY;

	bool isDead = false;
	bool spawned = false;

	virtual void Shoot();
	void Render();
	void CollisionCheck();
	void Dead();
	void SpawnCharacter(int x, int y, int width, int height);
	void MoveTowards();

	enum CollisionMask
	{
		PlayerMask, EnemyMask
	};

	SDL_Texture* charTexture;
	SDL_Texture* deadTexture;
	SDL_Rect charRect;

	SDL_Texture* flareTexture;
	SDL_Rect flareRect;
private:	
};

#endif