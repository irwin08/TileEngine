#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include "GameManager.h"

//platformer

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

int cameraX = 0;
int cameraY = 0;

void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Copter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gRenderer = NULL;
	gWindow = NULL;
	
	SDL_Quit();
}


int main(int argc, char *argv[])
{
	init();
	
	GameManager *gameManager = new GameManager(gRenderer);
	gameManager->loadMap("maps/copter.map", 200, 25);
	gameManager->loadCharacters("characters/associate.bmp", "characters/copter.char", 0, 0, 0);
	gameManager->Start();
	
	return 0;
}














