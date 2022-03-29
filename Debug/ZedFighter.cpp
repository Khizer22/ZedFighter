#include "stdafx.h"
#include "ZedFighter.h"

//CONSTRUCTOR MAIN GAME
JetFighterGame::JetFighterGame() {
	cout << "Main Game Created" << endl;
}

//DESCONSTRUCTOR MAIN GAME
JetFighterGame::~JetFighterGame(){
	//DESTORY SDL STUFF
	try {
		SDL_DestroyRenderer(ren);
	}
	catch (exception e) {
		cout << endl << "eh";
	}
	SDL_DestroyWindow(win);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}


//FULL GAME HERE
void JetFighterGame::StartGame() {

	InitializeSDL();
	SDL_Surface *screen = SDL_GetWindowSurface(win);

	//SET VIEWPORT
	Viewport = { 0,0, SCREENWIDTH , SCREENHEIGHT  };

	//CREATE GAME LEVEL
	GameLevel* gameLevel = new GameLevel(ren);

	//CREATE PLAYER
	Player* player = new Player(ren);
	//Assigns player health reference in game level (for enemies to use)
	gameLevel->playerHealth = &player->currentHealth;

	while (gameLoop) {

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		double deltaTime = deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * .001;

		//CLEAR SCREEN
		SDL_RenderClear(ren);		

		//SET VIEWPORT
		SDL_RenderSetViewport(ren, &Viewport);			

		//Game Level Update
		gameLevel->Update(deltaTime,player->xSpeed,player->ySpeed);

		//Player Update
		if (gameLevel->GetCurrentLevel() != 0 && player->spawned == false)
			player->SpawnCharacter(SCREENWIDTH / 2 - 30, SCREENHEIGHT / 2 - 40, 60, 80);
		if (player->isDead == false)
			player->Update(deltaTime, gameLevel->collidableObjects, gameLevel->enemyRects, gameLevel->enemyHealth);
		else {
			if (gameLevel->GetCurrentLevel() != 0) {
				cout << "\n--------------GAME OVER--------------\n";
				gameLevel->TransverseLevel(0);
				gameLevel->TransverseRound(-1);
			}
		}

		if (gameLevel->round >= 6) {
			if (gameLevel->GetCurrentLevel() != 0) {
				cout << "\n--------------------YOU WON!..................\n";
				gameLevel->TransverseLevel(0);
				gameLevel->TransverseRound(-1);
			}
		}

		while (SDL_PollEvent(&event)) {			
			//menu handle event
			if (gameLevel->GetCurrentLevel() == 0)
				gameLevel->HandleEventMenu(event,gameLoop);
			//player event handle
			player->HandleEvents(event);	
		}

		//RENDER EVERYTHING
		if (gameLoop)
			SDL_RenderPresent(ren);
	
		//gameLoop = false;
	}

	//DELETE STUFF
	delete gameLevel;
	delete player;
}

//INIT SDL STUFF
void JetFighterGame::InitializeSDL() {	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	SDL_Init(SDL_INIT_AUDIO);
	SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, NULL, &win, &ren);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}