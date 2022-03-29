#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "AIGun.h"

class EnemyGrunt : public Character {
public:
	EnemyGrunt(SDL_Renderer* ren,int spawnX, int spawnY);
	~EnemyGrunt();

	void Shoot();
	void Update(float deltaTime, float playerXSpeed,float playerYSpeed, vector<SDL_Rect*>collidableObjects, int* playerHealth);
	void Render();
	void SetStats(float maxSpeed,float maxHealth);
	void SetTexture(char* newTexture);
	void LoadGunAI(int _damage, float _fireRate, float _reloadTime, float _bulletVelocity, bool _singleFire, float _maxAmmo, char* fireTexture, char*bulletTexture, int bulletWidth, int bulletHeight);

	float xSpeed = 0, ySpeed = 0;

	AIGun* gun;
private:


	int state = 0;
	float changeDirecionTime = 0;
	float hiddenTime = 0;
	float randomDirection;
};

#endif