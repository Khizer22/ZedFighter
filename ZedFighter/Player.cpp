#include "stdafx.h"
#include "Player.h"

Player::Player(SDL_Renderer* _ren){
	ren = _ren;
	spawned = false;
	deltaTime = 0;

	//char create
	charTexture = IMG_LoadTexture(ren, "Images/player.png");

	//cursor create
	cursorTexture = IMG_LoadTexture(ren, "Images/Target.png");
	cursorRect = { 0,0,40,40 };

	//Gun create
	gun = new Gun(ren);
	gun->LoadGun(25,.2f, 1.5f, 1900, false, 30, gun->Rifle);

	//Flare create
	flareTexture = IMG_LoadTexture(ren, "Images/fire2.png");
	flareRect = { SCREENWIDTH/2 - 30,SCREENHEIGHT/2 - 110,60,220 };

	//Stats
	maxSpeed = 400;
	currentSpeed = 0;
	acceleration = 10;
	maxHealth = 100;
	currentHealth = maxHealth;

	CollisionMask mask = PlayerMask;
}


Player::~Player() {
	if (charTexture != NULL) {
		SDL_DestroyTexture(charTexture);
	}

	if (cursorTexture != NULL) {
		SDL_DestroyTexture(cursorTexture);
	}

	if (flareTexture != NULL) {
		SDL_DestroyTexture(flareTexture);
	}

	if (gun != NULL) {
		delete gun;
		gun = NULL;
	}

}

void Player::HandleEvents(SDL_Event &event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			leftPressed = true;
			break;
		case SDLK_d:
			rightPressed = true;
			break;
		case SDLK_w:
			upPressed = true;
			break;
		case SDLK_s:
			downPressed = true;
			break;
		default:
			break;
		}
		break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				leftPressed = false;
				break;
			case SDLK_d:
				rightPressed = false;
				break;
			case SDLK_w:
				upPressed = false;
				break;
			case SDLK_s:
				downPressed = false;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT: 
				firePressed = true;
				break;								
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT: 
				firePressed = false;
				break;			
			default:
				break;
			}
			break;
		default:
			break;		
	}	

	//Update Mouse Position
	SDL_GetMouseState(&mouseX, &mouseY);

}

void Player::Shoot() {
}

void Player::Update(float _deltaTime, vector<SDL_Rect*> collidableObjects , vector<SDL_Rect*>enemyRects,vector<int*> enemyHealth) {
	if (currentHealth <= 0)
		isDead = true;

	deltaTime = _deltaTime;	

	//Diagonal Movements
	if (rightPressed && upPressed)
	{
		direction = 125;
		MoveTowards();
	}
	else if (upPressed && leftPressed)
	{
		direction = -125;
		MoveTowards();
	}
	else if (downPressed && leftPressed)
	{
		direction = -35;
		MoveTowards();
	}
	else if (downPressed && rightPressed)
	{
		direction = 35;
		MoveTowards();
	}
	else if (leftPressed && rightPressed)
	{
		//rotation = 35;
		currentSpeed = 0;
	}
	else if (upPressed && downPressed)
	{
		//rotation = 35;
		currentSpeed = 0;
	}
	//Straight Movements
	else if (leftPressed) {
		direction = -90;
		MoveTowards();
	}
	else if (rightPressed)
	{
		direction = 90;
		MoveTowards();
	}
	else if (upPressed)
	{
		direction = 180;
		MoveTowards();
	}
	else if (downPressed)
	{
		direction = 0;
		MoveTowards();
	}
	else {
		if (currentSpeed > 0) {
			currentSpeed -= acceleration;
		}
		else if (currentSpeed < 0)
			currentSpeed = 0;
	}

	double radians = (3.14 / 180)*direction;
	xSpeed = sin(radians) * (currentSpeed * deltaTime);
	ySpeed = cos(radians) * (currentSpeed * deltaTime);

	posX += xSpeed;
	posY += ySpeed;

	//charRect.x = posX;
	//charRect.y = posY;

	//Calculate Collision with static objects
	for (int i = 0; i < collidableObjects.size(); i++)
	{
		if (charRect.x + charRect.w  + xSpeed> collidableObjects.at(i)->x
			&& charRect.x + xSpeed < collidableObjects.at(i)->x + collidableObjects.at(i)->w
			&& charRect.y + charRect.h + ySpeed > collidableObjects.at(i)->y
			&& charRect.y + ySpeed < collidableObjects.at(i)->y + collidableObjects.at(i)->h
			) {
			ySpeed -= (ySpeed * 1.01f);
			xSpeed -= (xSpeed * 1.01f);
		}
	}

	//Calculate Mouse Position
	angle = -(180 / 3.14)*(atan2(mouseX - SCREENWIDTH / 2, mouseY - SCREENHEIGHT / 2));

	//Update Curosr
	cursorRect.x = mouseX - cursorRect.w/2;
	cursorRect.y = mouseY - cursorRect.h/2;
	
	//Shoot gun
	if (firePressed == true ) {
		gun->ShootUpdate(angle, SCREENWIDTH / 2 - 13, SCREENHEIGHT / 2 - 45.5f);
	}	

	//gun Update	
	gun->Update(deltaTime,xSpeed,ySpeed, collidableObjects, enemyRects,enemyHealth);

	//Render Everything
	if (spawned) {
		Render();
	}
}

void Player::Render() {	 	
	gun->Render();	

	SDL_RenderCopyEx(ren, charTexture, NULL, &charRect, angle, NULL, SDL_FLIP_VERTICAL);

	if (gun->currentFireTime > gun->fireRate - 0.1f)
		SDL_RenderCopyEx(ren, flareTexture, NULL, &flareRect, angle, NULL, SDL_FLIP_VERTICAL);

	//probably need a seperate function to render cursor, so I can lateer render it on top of EVERYTHING
	SDL_RenderCopy(ren, cursorTexture, NULL, &cursorRect);
}
