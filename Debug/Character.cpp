#include "stdafx.h"
#include "Character.h"

Character::~Character() {
	
}

void Character::Render() {
	SDL_RenderCopyEx(ren, charTexture, NULL, &charRect, angle, NULL, SDL_FLIP_VERTICAL);
}

void Character::Shoot() {
}

void Character::Update(float deltaTime, float playerXSpeed, float playerYSpeed) {

}

void Character::Update(float deltaTime, float playerXSpeed, float playerYSpeed, vector<SDL_Rect*>collidableObjects, int* playerHealth) {}

void Character::SpawnCharacter(int x, int y, int _width, int _height) {
	posX = x;
	posY = y;
	width = _width;
	height = _height;

	charRect = { x,y,_width,_height };

	spawned = true;
}

void Character::MoveTowards() {
	if (currentSpeed < maxSpeed) {
		currentSpeed += acceleration;
	}
	else
		currentSpeed = maxSpeed;
}

void Character::CollisionCheck() {
	//cout << "CollisionCheck";
}

void Character::SetStats(float _maxSpeed, float _maxHealth) {

}

void Character::LoadGunAI(int _damage, float _fireRate, float _reloadTime, float _bulletVelocity, bool _singleFire, float _maxAmmo, char* fireTexture, char*bulletTexture, int bulletWidth, int bulletHeight) {}

void Character::SetTexture(char* newTexture) {

}

void Character::Dead() {

}

float Character::GetX() {
	return posX;
}

float Character::GetY() {
	return posY;
}

float Character::GetCurrentSpeed() {
	return currentSpeed;
}

float Character::GetMovingDirection() {
	return direction;
}