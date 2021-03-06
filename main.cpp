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
	gWindow = SDL_CreateWindow("TileEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
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
	gameManager->loadMap("maps/clayton.map", 100, 37);
	gameManager->loadCharacters("characters/associate.bmp", "characters/walmart.char", 50, 50, 2);
	gameManager->Start();
	
	return 0;
}


