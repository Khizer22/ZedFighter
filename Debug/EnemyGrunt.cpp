#include "stdafx.h"
#include "EnemyGrunt.h"

EnemyGrunt::EnemyGrunt(SDL_Renderer* _ren,int spawnX, int spawnY) {
	ren = _ren;
	charTexture = IMG_LoadTexture(ren, "Images/grunt.png");
	deadTexture = IMG_LoadTexture(ren, "Images/splat1.png");
	
	gun = new AIGun(ren);
	gun->LoadGun(20, .5f, 1, 500, false, 10, gun->Rifle);

	//Stats
	maxHealth = 75;
	currentHealth = maxHealth;
	maxSpeed = 100;
	currentSpeed = 0;
	acceleration = 10;
	changeDirecionTime = 0;
	randomDirection = ((float(rand()) / float(RAND_MAX)) * (180 - -180)) + -180;
	hiddenTime = 0;

	CollisionMask mask = EnemyMask;

	//if (!spawned)
		//SpawnCharacter(spawnX, spawnY,60,80);
}


EnemyGrunt::~EnemyGrunt() {
	if (charTexture != NULL)
	{
		SDL_DestroyTexture(charTexture);
		charTexture = NULL;
	}

	if (deadTexture != NULL)
	{
		SDL_DestroyTexture(deadTexture);
		deadTexture = NULL;
	}

	if (gun != NULL)
	{
		delete gun;
		gun == NULL;
	}
}

void EnemyGrunt::Update(float deltaTime, float playerXSpeed, float playerYSpeed,vector<SDL_Rect*>collidableObjects, int* playerHealth) {
	if (currentHealth <= 0)
		isDead = true;

	float randomAngle = ((float(rand()) / float(RAND_MAX)) * (15 - -15)) + -15;

	if (!isDead) {	
		if (state == 0) { //idle
			state = 1;
			if (posX + charRect.w > 0 && posX < SCREENWIDTH - charRect.w / 2
				&& posY + charRect.h > 0 && posY < SCREENHEIGHT - charRect.h / 2) {
				state = 1;
			}
		}
		else if (state == 1) { //in Screen	 (moves around)
			if (hiddenTime > 3) {
				state = 2;
				hiddenTime = 0;
			}
			changeDirecionTime += deltaTime;

			if (changeDirecionTime > 1)
			{
				randomDirection = ((float(rand()) / float(RAND_MAX)) * (180 - -180)) + -180;
				changeDirecionTime = 0;
				//cout << "\nChanged direction (in state 1)";
			}
		}
		else if (state == 2) { //Out of screen (moves towards player)
			if (posX + charRect.w > 0 && posX < SCREENWIDTH
				&& posY + charRect.h > 0 && posY < SCREENHEIGHT) {
				hiddenTime += deltaTime;
			}

			if (hiddenTime > 1) {
				state = 1;
				hiddenTime = 0;
			}
			randomDirection = 0;
		}

		if (state != 0) {
			float dirX;
			float dirY;
			if (playerXSpeed > 0)
				dirX = 1.15f;
			else if (playerXSpeed < 0)
				dirX = 0.85f;
			else dirX = 1;

			if (playerYSpeed > 0)
				dirY = 1.15f;
			else if (playerYSpeed < 0)
				dirY = 0.85f;
			else dirY = 1;

			float XTHING = (posX + 30) - (SCREENWIDTH / 2 * dirX);
			float YTHING = (posY + 40) - (SCREENHEIGHT / 2 * dirY);
			angle = -(180 / 3.14)*(atan2(XTHING, YTHING));

			//AI behaviour here
			//Gun Update	
			if (posX + charRect.w > 0 && posX < SCREENWIDTH
				&& posY + charRect.h > 0 && posY < SCREENHEIGHT) {
				gun->ShootUpdate(angle + randomAngle, posX + 30, posY + 40);
			}
			else {
				if (state == 1)
					hiddenTime += deltaTime;
			}

			//Moving around
			MoveTowards();
			double radians = (3.14 / 180)*(angle + randomDirection);
			xSpeed = sin(radians) * (currentSpeed * deltaTime);
			ySpeed = cos(radians) * (currentSpeed * deltaTime);

			posX += xSpeed;
			if (state != 2)
				posY += ySpeed;
			else posY -= ySpeed;

			//needa fix
			//Calculate Collision with static objects
			for (int i = 0; i < collidableObjects.size(); i++)
			{
				if (charRect.x + charRect.w + xSpeed > collidableObjects.at(i)->x
					&& charRect.x + xSpeed < collidableObjects.at(i)->x + collidableObjects.at(i)->w
					&& charRect.y + charRect.h + ySpeed > collidableObjects.at(i)->y
					&& charRect.y + ySpeed < collidableObjects.at(i)->y + collidableObjects.at(i)->h
					) {
					posY -= (ySpeed * 1.01f);
					posX -= (xSpeed * 1.01f);
				}
			}
		}
	}
	gun->Update(deltaTime, playerXSpeed, playerYSpeed, collidableObjects, playerHealth);

	//Player position offset
	posX -= playerXSpeed;
	posY -= playerYSpeed;

	charRect.x = posX;
	charRect.y = posY;

	//Render
	if (spawned)
		Render();
}

void EnemyGrunt::SetStats(float _maxSpeed, float _maxHealth) {	
	maxHealth = _maxHealth;
	currentHealth = _maxHealth;
	maxSpeed = _maxSpeed;
}

void EnemyGrunt::SetTexture(char* newTexture) {
	charTexture = NULL;
	charTexture = IMG_LoadTexture(ren, newTexture);
}

void EnemyGrunt::LoadGunAI(int _damage, float _fireRate, float _reloadTime, float _bulletVelocity, bool _singleFire, float _maxAmmo, char* fireTexture, char*bulletTexture, int bulletWidth, int bulletHeight) {
	gun->LoadGun(_damage,_fireRate,_reloadTime,_bulletVelocity,_singleFire,_maxAmmo,gun->Rifle);
	gun->SetTextures(fireTexture, bulletTexture);
	gun->SetProjectileSize(bulletWidth, bulletHeight);

}

void EnemyGrunt::Shoot() {	
}

void EnemyGrunt::Render() {
	gun->Render();	

	//Render if in Screen
	if (charRect.x < SCREENWIDTH
		&& charRect.x  + charRect.w > 0
		&& charRect.y + charRect.h > 0
		&& charRect.y < SCREENHEIGHT) {		
		if (!isDead)
			SDL_RenderCopyEx(ren, charTexture, NULL, &charRect, angle, NULL, SDL_FLIP_NONE);
		else 
			SDL_RenderCopyEx(ren, deadTexture, NULL, &charRect, angle, NULL, SDL_FLIP_NONE);
	}
	
	//if (gun->currentFireTime > 0.1f)
		//SDL_RenderCopyEx(ren, flareTexture, NULL, &flareRect, angle, NULL, SDL_FLIP_VERTICAL);
}