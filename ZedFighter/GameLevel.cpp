#include "stdafx.h"
#include "GameLevel.h"

GameLevel::GameLevel(SDL_Renderer* _ren) {
	ren = _ren;

	wallBuilder = new Wall(ren);
	props = new Props(ren);

	CreateLevel(0);
	tilesCreated = false;

	round = 1;

	//UI
	healthRect = { 50,SCREENHEIGHT - 50,200,75 };
	healthTex = IMG_LoadTexture(ren, "Images/h.png");
	CreateFont(ren, UIHealthTex, &UIHealthRect, "Health:", 50, SCREENHEIGHT - 100, 100, 50, { 255,255,255 });
}

GameLevel::~GameLevel() {
	//DESTROY TEXTURE
	if (backgroundTex != NULL) {
		SDL_DestroyTexture(backgroundTex);
	}

	//Delete Wall
	if (wallBuilder != NULL)
	{
		delete wallBuilder;
		wallBuilder = NULL;
	}

	//DELETE MENU
	if (mainMenu != NULL) {
		delete mainMenu;
		mainMenu = NULL;
	}

	//Delete Enemies and stuff
	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			delete enemies.at(i);
		}
		enemies.clear();
		enemyRects.clear();
		enemyHealth.clear();
	}
	collidableObjects.clear();

	//DELETE PROPS
	if (props != NULL) {
		delete props;
		props = NULL;
	}

	if (healthTex != NULL)
	{
		SDL_DestroyTexture(healthTex);
		healthTex = NULL;
	}

	if (UIHealthTex != NULL)
	{
		SDL_DestroyTexture(UIHealthTex);
		UIHealthTex = NULL;
	}
}

//RENDER
void GameLevel::Render() {
	for (int i = 0; i < TILE_AMOUNT; i++) {
		SDL_RenderCopy(ren, backgroundTex, NULL, &backgroundRect[i]);		
	}		
}

//UPDATE
void GameLevel::Update(float deltaTime,float playerX, float playerY) {
	if (currentLevel == 0)
		mainMenu->Update(deltaTime); //renders menu here as well
	else {
		BackgroundTileUpdate(playerX, playerY); //Shuffles bg Tiles
		Render(); //Renders bg Tiles

		props->UpdateAllProps(playerX,playerY);

		wallBuilder->UpdateAllWalls(playerX, playerY);

		for (int i = 0; i < enemies.size(); i++)
			enemies.at(i)->Update(deltaTime, playerX, playerY, collidableObjects, playerHealth);

		//Update UI
		SDL_RenderCopy(ren, UIHealthTex, NULL, &UIHealthRect);
		healthRect.w = (*playerHealth);
		SDL_RenderCopy(ren, healthTex, NULL, &healthRect);

		RoundUpdate();
	}
}

void GameLevel::HandleEventMenu(SDL_Event &event, bool &gameLoop) {
	if (mainMenu != NULL) {
		int choice = mainMenu->HandleEvent(event);

		if (choice == 1)
		{
			TransverseLevel(1);
		}
		else if (choice == 2)
		{
			gameLoop = false;
		}
	
	}
}

//CREATE SPECIFIED LEVEL - ALSO HOLDS INFORMATION ABOUT ALL LEVELS
void GameLevel::CreateLevel(int level) {
	currentLevel = level;

	//Create tiles for in game levels regardless of menu, since all stages will use these
	if (tilesCreated == false) {
		int tileX = 0;
		int tileY = 0;
		for (int i = 0; i < TILE_AMOUNT; i++) {

			if (tileX == 4) {
				tileX = 0;
				tileY += 1;
			}
			backgroundRect[i] = { -TILE_WIDTH + (TILE_WIDTH * tileX),tileY * TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT };
			bgX[i] = -TILE_WIDTH + (TILE_WIDTH * tileX);
			bgY[i] = tileY * TILE_HEIGHT;
			tileX += 1;
		}
		tilesCreated = true;
	}

	//Level Specific Stuff
	if (level == 0) {
		//Creat Menu 
		if (mainMenu == NULL)
			mainMenu = new Menu(ren);

		SDL_ShowCursor(SDL_ENABLE);
	}
	//LEVEL 1
	else if (level == 1) {
		//create the first level texture
		backgroundTex = IMG_LoadTexture(ren, "Images/background3new.png");
		SDL_ShowCursor(SDL_DISABLE);

		
		//enemies.at(1)

		//Create Walls
		//BOUNDRIES
		wallBuilder->BuildWallAndCorner(-500, 800, 7, 1, false);
		wallBuilder->BuildWallAndCorner(-500, -1268, 7, 1, false);
		wallBuilder->BuildWallAndCorner(-500, 800,10,0,false);
		wallBuilder->BuildWallAndCorner(1100, 800,10, 0, false);

		//Cover
		wallBuilder->BuildCorner(-200, 100);
		wallBuilder->BuildCorner(-100, 100);
		wallBuilder->BuildWallAndCorner(-200, -500, 1, 1, false);
		wallBuilder->BuildWallAndCorner(-200, -100, 1, 1, false);
		wallBuilder->BuildWallAndCorner(-200, 200, 1, 1, false);
		wallBuilder->BuildWallAndCorner(400, -100, 1, 1, false);
		wallBuilder->BuildWallAndCorner(400, -500, 1, 1, false);

		//Create Props
		props->SpawnProp(404, -1180, 292, 292, "Images/SpaceThingy2.png");
		props->SpawnProp(500, 100, 247, 326, "Images/car.png");

		//Point all collidable objects to a vector of Rects
		for (int i = 0; i < wallBuilder->blockRects.size(); i++)
		{
			collidableObjects.push_back(&wallBuilder->blockRects.at(i));
		}
		for (int i = 0; i < wallBuilder->wallRects.size(); i++) {
			collidableObjects.push_back(&wallBuilder->wallRects.at(i));
		}		
		for (int i = 0; i < props->propRects.size(); i++) {
			collidableObjects.push_back(&props->propRects.at(i));
		}
		//Create Trigger Prop
		props->SpawnTriggerProp(-500, -1200, 340, 340, "Images/groundDecal.png");
		props->SpawnTriggerProp(-500, -10, 340, 340, "Images/groundDecal.png");
		props->SpawnTriggerProp(500, 250, 340, 340, "Images/groundDecal.png");
		props->SpawnTriggerProp(-200, -250, 340, 340, "Images/groundDecal.png");
		props->SpawnTriggerProp(900, -0, 340, 340, "Images/groundDecal.png");
		props->SpawnTriggerProp(0, 0, 340, 340, "Images/groundDecal.png");
	}
	//LEVEL 2 not using 
	else if (level == 2) {
		//create the second level texture
		backgroundTex = IMG_LoadTexture(ren, "Images/background1new.png");
		SDL_ShowCursor(SDL_DISABLE);

		//Create Enemies
		enemies.push_back(new EnemyGrunt(ren,100,100));

		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}

		//Create Walls
		wallBuilder->BuildCorner(950, 50);

		wallBuilder->BuildWallAndCorner(500, 500, 4, 1, false);

		//Point all collidable objects to a vector of Rects
		for (int i = 0; i < wallBuilder->blockRects.size(); i++)
		{
			collidableObjects.push_back(&wallBuilder->blockRects.at(i));
		}
		for (int i = 0; i < wallBuilder->wallRects.size(); i++) {
			collidableObjects.push_back(&wallBuilder->wallRects.at(i));
		}
	}
}

void GameLevel::TransverseRound(int Round) {
	//Regardless of level, clear all enemies and walls (and props if i add them)
	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			delete enemies.at(i);
		}
		enemies.clear();
		enemyRects.clear();
		enemyHealth.clear();
	}
	//Create Enemies
	if (round == 1) {
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(0)->SpawnCharacter(-400, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(1)->SpawnCharacter(-400, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(2)->SpawnCharacter(900, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(3)->SpawnCharacter(900, 600, 60, 80);	

		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}
	}
	else if (round == 2) {
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(0)->SpawnCharacter(-400, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(1)->SpawnCharacter(-400, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(2)->SpawnCharacter(900, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(3)->SpawnCharacter(900, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(4)->SpawnCharacter(-300, 800, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(5)->SpawnCharacter(-300, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(6)->SpawnCharacter(810, -600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(7)->SpawnCharacter(750, -230, 80, 100);
		enemies.at(7)->SetStats(200, 300);
		

		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}
	}
	else if (round == 3) {
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(0)->SpawnCharacter(550, -350, 129, 186);
		enemies.at(0)->SetTexture("Images/mutant.png");
		enemies.at(0)->SetStats(10, 1000);
		enemies.at(0)->LoadGunAI(120, 3, 1, 1500, false, 19, "Images/mutantCharge.png", "Images/mutantBullet.png", 122, 300);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(1)->SpawnCharacter(-400, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(2)->SpawnCharacter(900, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(3)->SpawnCharacter(900, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(4)->SpawnCharacter(-200, 600, 69, 129);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(5)->SpawnCharacter(900, 600, 69, 129);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(6)->SpawnCharacter(-250, 600, 69, 129);
		for (int i = 0; i < enemies.size(); i++) {
			if (i > 3) {
				enemies.at(i)->SetTexture("Images/assault.png");
				enemies.at(i)->SetStats(500, 100);
				enemies.at(i)->LoadGunAI(35, 1, 1, 1000, false, 19, "Images/mutantCharge.png", "Images/assaultFire.png", 64, 138);
			}
		}

		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}
	}
	else if (round == 4) {
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(0)->SpawnCharacter(-400, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(1)->SpawnCharacter(-400, 600, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(2)->SpawnCharacter(900, -1000, 60, 80);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(3)->SpawnCharacter(900, 600, 100, 120);
		enemies.at(3)->SetStats(200, 500);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(4)->SpawnCharacter(-300, 600, 69, 129);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(5)->SpawnCharacter(500, 600, 69, 129);
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(6)->SpawnCharacter(-200, -600, 129, 186);
		for (int i = 0; i < enemies.size(); i++) {
			if (i > 3 && i != 6) {
				enemies.at(i)->SetTexture("Images/assault.png");
				enemies.at(i)->SetStats(500, 150);
				enemies.at(i)->LoadGunAI(50, 1, 1, 1000, false, 19, "Images/mutantCharge.png", "Images/assaultFire.png", 64, 138);
			}
			if (i == 6) {
				enemies.at(i)->SetTexture("Images/mutant.png");
				enemies.at(i)->SetStats(10, 1500);
				enemies.at(i)->LoadGunAI(250, 3, 1, 2000, false, 19, "Images/mutantCharge.png", "Images/mutantBullet.png", 122, 300);
			}
		}

		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}
	}
	else if (round == 5) {
		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(0)->SpawnCharacter(-400, -1000, 64, 138);
		enemies.at(0)->SetTexture("Images/assault.png");
		enemies.at(0)->SetStats(500, 150);
		enemies.at(0)->LoadGunAI(65, 1, 1, 1000, false, 19, "Images/mutantCharge.png", "Images/assaultFire.png", 64, 138);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(1)->SpawnCharacter(-400, -1000, 64, 138);
		enemies.at(1)->SetTexture("Images/assault.png");
		enemies.at(1)->SetStats(500, 150);
		enemies.at(1)->LoadGunAI(55, 1, 1, 1000, false, 19, "Images/mutantCharge.png", "Images/assaultFire.png", 64, 138);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(2)->SpawnCharacter(900, -1000, 80, 100);
		enemies.at(2)->SetStats(200, 500);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(3)->SpawnCharacter(900, -400, 129, 186);
		enemies.at(3)->SetTexture("Images/mutant.png");
		enemies.at(3)->SetStats(10, 1500);
		enemies.at(3)->LoadGunAI(500, 3, 1, 2000, false, 19, "Images/mutantCharge.png", "Images/mutantBullet.png", 122, 300);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(4)->SpawnCharacter(-300, 600, 100, 120);
		enemies.at(4)->SetStats(200, 500);

		enemies.push_back(new EnemyGrunt(ren, 100, 100));
		enemies.at(5)->SpawnCharacter(100, -500, 129, 186);
		enemies.at(5)->SetTexture("Images/mutant.png");
		enemies.at(5)->SetStats(10, 1500);
		enemies.at(5)->LoadGunAI(500, 3, 1, 2000, false, 19, "Images/mutantCharge.png", "Images/mutantBullet.png", 122, 300);
		
		//Store enemy rects in vector
		for (int i = 0; i < enemies.size(); i++)
		{
			enemyRects.push_back(&enemies.at(i)->charRect);
			enemyHealth.push_back(&enemies.at(i)->currentHealth);
		}
	}	
}

//MOVES TILES WHEN OUT OF RANGE
void GameLevel::BackgroundTileUpdate(float playerXSpeed, float playerYSpeed) {

	int tileX = 0;
	int tileY = 0;	

	for (int i = 0; i < TILE_AMOUNT; i++) {	

		bgX[i] -= playerXSpeed;
		bgY[i] -= playerYSpeed;

		if (bgX[i] >= SCREENWIDTH + TILE_WIDTH / 2) {
			bgX[i] -= (TILE_WIDTH * 4);
			//cout << "MOVED LEFT";
		}
		else if (bgX[i] < -TILE_WIDTH * 1.5) {
			bgX[i] += TILE_WIDTH * 4;
			//cout << "MOVED RIGHT";
		}
		else if (bgY[i] >= SCREENHEIGHT + TILE_HEIGHT / 4) {
			bgY[i] -= TILE_HEIGHT * 3;
			//cout << "MOVED UP";
		}
		else if (bgY[i] <= -TILE_HEIGHT) {
			bgY[i] += TILE_HEIGHT * 3;
			//cout << "MOVED DOWN";
		}


		backgroundRect[i].x = bgX[i];
		backgroundRect[i].y = bgY[i];
	}
}

void GameLevel::RoundUpdate() {
	int kills = 0;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies.at(i)->isDead == true) {
			killCount++;
			kills++;
		}
		else kills--;		
			
	}
	if (kills == enemies.size()) {
		if (round < 6) {
			round++;
			cout << "\n\n.........................Round: " << round <<".........................\n\n";
			TransverseLevel(1);
			*playerHealth = 100 + (round * 50);
			//TransverseRound(round);
		}
	}
}

int GameLevel::GetCurrentLevel() {
	return currentLevel;
}

//Transverse Level not used anymore
void GameLevel::TransverseLevel(int level) {
	wallBuilder->ClearAllWalls();
	props->ClearAllProps();
	collidableObjects.clear();

	if (level != 0)
	{
		if (mainMenu != NULL) {
			delete mainMenu;
			mainMenu = NULL;
		}
	}
	else if (level == 0) {

		if (mainMenu == NULL)
			mainMenu = new Menu(ren);

		if (backgroundTex != NULL) {
			SDL_DestroyTexture(backgroundTex);
			backgroundTex = NULL;
		}
		CreateLevel(0);
	}

	if (level == 1) {
		if (backgroundTex != NULL) {
			SDL_DestroyTexture(backgroundTex);
			backgroundTex = NULL;
		}
		enemiesToSpawn = 5;
		CreateLevel(1);
		TransverseRound(round);
	}
	else if (level == 2) {
		if (backgroundTex != NULL) {
			SDL_DestroyTexture(backgroundTex);
			backgroundTex = NULL;
		}
		enemiesToSpawn = 10;
		CreateLevel(2);
	}
}


