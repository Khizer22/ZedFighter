#include "stdafx.h"
#include "AIGun.h"

AIGun::AIGun(SDL_Renderer* _ren) {
	ren = _ren;

	projectileTexture = IMG_LoadTexture(ren, "Images/shoot.png");
	destroyTexture = IMG_LoadTexture(ren, "Images/fireHit.png");

	//SDL_SetTextureAlphaMod(destroyTexture, 150);
	projectileRect = { {},{},{},{},{} };
	posX = { {},{},{},{},{} };
	posY = { {},{},{},{},{} };
	xSpeed = { {},{},{},{},{} };
	ySpeed = { {},{},{},{},{} };
	angle = { {},{},{},{},{} };
	bulletLife = { {},{},{},{},{} };
	destroyed = { {},{},{},{},{} };
	destroyTime = { {},{},{},{},{} };
	inUse = { {},{},{},{},{} };

	for (int i = 0; i < bulletVectorLength; i++) {
		posX.at(i) = 0;
		posY.at(i) = 0;
		xSpeed.at(i) = 0;
		ySpeed.at(i) = 0;
		angle.at(i) = 0;
		bulletLife.at(i) = 0;
		destroyed.at(i) = false;
		destroyTime.at(i) = 0;
		inUse.at(i) = false;
		projectileRect.at(i) = { 0,0,26,91 };
	}

	//sounds = new Sounds();
}

AIGun::~AIGun() {
	if (projectileTexture != NULL) {
		SDL_DestroyTexture(projectileTexture);
		projectileTexture = NULL;
	}
	if (destroyTexture != NULL) {
		SDL_DestroyTexture(destroyTexture);
		destroyTexture = NULL;
	}

	/*
	if (sounds != NULL) {
		delete sounds;
		sounds = NULL;
	}
	*/

}

void AIGun::Render() {
	for (int i = 0; i < bulletVectorLength; i++) {
		if (inUse.at(i) == true && destroyed.at(i) == false) {
			SDL_RenderCopyEx(ren, projectileTexture, NULL, &projectileRect.at(i), angle.at(i), NULL, SDL_FLIP_NONE);
		}
		else if (destroyed.at(i))
			SDL_RenderCopyEx(ren, destroyTexture, NULL, &projectileRect.at(i), angle.at(i), NULL, SDL_FLIP_NONE);
	}
}

void AIGun::ShootUpdate(float _angle, int x, int y) {
	x -= 13; //size of projhectile rect
	y -= 45.5f;
	bool used = false;
	if (currentFireTime <= 0) {
		for (int i = 0; i < bulletVectorLength; i++) {
			if (inUse.at(i) == false) {
				//SHOOT
				//sounds->Play("shoot");
				posX.at(i) = x;
				posY.at(i) = y;
				angle.at(i) = _angle;
				inUse.at(i) = true;
				currentFireTime = fireRate;
				used = true;
			}
			if (used)
				break;
		}
	}
}

void AIGun::Update(float deltaTime, float playerXSpeed, float playerYSpeed, vector<SDL_Rect*> collidableObjects, int* playerHealth) {
	for (int i = 0; i < bulletVectorLength; i++) {
		if (inUse.at(i) == true && destroyed.at(i) == false) {
			//Updates location and speed
			double radians = (3.14 / 180)*angle.at(i);
			xSpeed.at(i) = sin(radians) * (-bulletVelocity * deltaTime);
			ySpeed.at(i) = cos(radians) * (bulletVelocity * deltaTime);

			posX.at(i) -= xSpeed.at(i) + playerXSpeed;
			posY.at(i) -= ySpeed.at(i) + playerYSpeed;

			projectileRect.at(i).x = posX.at(i);
			projectileRect.at(i).y = posY.at(i);

			//Collision with Enemies
			if (projectileRect.at(i).x + (projectileRect.at(i).w * 0.8f) > SCREENWIDTH/2 - 30
				&& projectileRect.at(i).x + (projectileRect.at(i).w * 0.2f) <  SCREENWIDTH / 2 + 30 
				&& projectileRect.at(i).y + (projectileRect.at(i).h * .5f) > SCREENHEIGHT/2 - 40
				&& projectileRect.at(i).y + (projectileRect.at(i).h * 0.5f)  < SCREENHEIGHT / 2 + 40
				&& *playerHealth > 0
				) {
				//sounds->Play("shoot2");
				destroyed.at(i) = true;
				inUse.at(i) = true;
				*playerHealth -= damage;
				SDL_SetTextureColorMod(destroyTexture, 255, 0, 0);
			}
			

			//Calculate Collision with static objects
			
			for (int q = 0; q < collidableObjects.size(); q++)
			{
				if (projectileRect.at(i).x + (projectileRect.at(i).w * 0.8f) > collidableObjects.at(q)->x
					&& projectileRect.at(i).x + (projectileRect.at(i).w * 0.2f) < collidableObjects.at(q)->x + collidableObjects.at(q)->w
					&& projectileRect.at(i).y + (projectileRect.at(i).h * .5f) > collidableObjects.at(q)->y
					&& projectileRect.at(i).y + (projectileRect.at(i).h * 0.5f)  < collidableObjects.at(q)->y + collidableObjects.at(q)->h
					) {
					//sounds->Play("hit");
					destroyed.at(i) = true;
					inUse.at(i) = true;
					SDL_SetTextureColorMod(destroyTexture, 255, 255, 255);
				}
			}
			

			//Puts bullet back in arsenol after 1 second
			bulletLife.at(i) += deltaTime;
			if (bulletLife.at(i) > 1)
			{
				inUse.at(i) = false;
				bulletLife.at(i) = 0;
			}
		}

		if (destroyTime.at(i) > .2f) {
			destroyed.at(i) = false;
			inUse.at(i) = false;
			bulletLife.at(i) = 0;
			destroyTime.at(i) = 0;
		}

		if (destroyed.at(i)) {

			posX.at(i) -= playerXSpeed;
			posY.at(i) -= playerYSpeed;

			projectileRect.at(i).x = posX.at(i);
			projectileRect.at(i).y = posY.at(i);

			inUse.at(i) = true;
			destroyTime.at(i) += deltaTime;
		}
	}

	if (currentFireTime > 0)
		currentFireTime -= deltaTime;
	else if (currentFireTime < 0)
		currentFireTime = 0;
}

void AIGun::LoadGun(int _damage, float _fireRate, float _reloadTime, float _bulletVelocity, bool _singleFire, float _maxAmmo, enum gunType) {
	damage = _damage;
	fireRate = _fireRate;
	reloadTime = _reloadTime;
	bulletVelocity = _bulletVelocity;
	singleFire = _singleFire;
	maxAmmo = _maxAmmo;
	//gunType = gunType;

}

void AIGun::SetTextures(char* fireTexture,char* bulletTexture) {
	projectileTexture = NULL;
	destroyTexture = NULL;
	projectileTexture = IMG_LoadTexture(ren,bulletTexture);
	destroyTexture = IMG_LoadTexture(ren,fireTexture);
}

void AIGun::SetProjectileSize(int width, int height) {
	for (int i = 0; i < projectileRect.size(); i++) {
		projectileRect.at(i).w = width;
		projectileRect.at(i).h = height;
	}
}

void AIGun::CollisionCheck(enum collisionMask) {
}

void AIGun::Reload() {

}
