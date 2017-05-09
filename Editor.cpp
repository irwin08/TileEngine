#include <SDL2/SDL.h>
#include "Map.h"
#include <memory>
#include <iostream>
#include <fstream>

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

int cameraX = 0;
int cameraY = 0;

void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
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
	
	int editType = 1;
	
	
	char c;
	
	std::cout << "Would you like to create a new map? ";
	std::cin >> c;
	
	std::shared_ptr<Map>map;
	
	if(c == 'y')
	{
		std::cout << std::endl << "New map: ";
		std::string filename;
		std::cin >> filename;
		std::cout << std::endl << "Please specify map size." << std::endl << "x:";
		int x;
		std::cin >> x;
		std::cout << std::endl << "y:";
		int y;
		std::cin >> y;
		std::cout << std::endl;
		
		map.reset(new Map(gRenderer, x, y, filename.c_str(), true, true));
	}
	else
	{
		std::cout << std::endl << "Load map: ";
		std::string filename;
		std::cin >> filename;
		std::cout << std::endl << "Please specify map size." << std::endl << "x:";
		int x;
		std::cin >> x;
		std::cout << std::endl << "y:";
		int y;
		std::cin >> y;
		std::cout << std::endl;
		
		map.reset(new Map(gRenderer, x, y, filename.c_str(), true, false));
	}
	
	
	int quit = 0;
	SDL_Event e;
	
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				quit = 1;
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_COMMA:
						editType--;
						//set 2 to max number of tiletypes
						if(editType < 1)
							editType = 5;
						std::cout << "Edit Type: " << editType << std::endl;
						break;
					case SDLK_PERIOD:
						editType++;
						if(editType > 5)
							editType = 1;
						std::cout << "Edit Type: " << editType << std::endl;
						break;
					case SDLK_UP:
						cameraY -= 20;
						if(cameraY < 0)
							cameraY = 0;
						break;
					case SDLK_DOWN:
						cameraY += 20;
						if((cameraY/20) > map->getY())
							cameraY = 20*map->getY();
						break;
					case SDLK_LEFT:
						cameraX -= 20;
						if(cameraX < 0)
							cameraX = 0;
						break;
					case SDLK_RIGHT:
						cameraX += 20;
						std::cout << cameraX << std::endl;
						if((cameraX/20) > map->getX())
							cameraX = 20*map->getX(); 
						break;
					case SDLK_s:
						map->saveMap();
						std::cout << "Map '" << map->getFilePath() << "' saved." << std::endl;
						break;
				}
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				
				int row = x/20;
				int column = y/20;
				
				if((row+(cameraX/20)) < map->getX())
				{
					if((column+(cameraY/20)) < map->getY())
					{
						map->changeTileType(editType, (row+(cameraX/20)),(column+(cameraY/20)));
						std::cout << "Tile " << (row+(cameraX/20)) << " " << (column+(cameraY/20)) << " changed." << std::endl; 
					}
				}
				
			}
		}
		
		
		
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(gRenderer);

		map->render(gRenderer, cameraX, cameraY);

		SDL_RenderPresent(gRenderer);
	}
	
	return 0;
}


