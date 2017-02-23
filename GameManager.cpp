#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

GameManager::GameManager(SDL_Renderer *renderer)
{
	cameraX = 0;
	cameraY = 0;
	mRenderer = renderer;
	quit = 0;
}

void GameManager::Start()
{
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
					case SDLK_w:
						player->moveUp(&cameraX, &cameraY);
						if(checkCollision(player, true))
							player->moveDown(&cameraX, &cameraY, 200);
						break;
					case SDLK_s:
						player->moveDown(&cameraX, &cameraY, 200);
						if(checkCollision(player, true))
							player->moveUp(&cameraX, &cameraY);
						break;
					case SDLK_a:
						player->moveLeft(&cameraX, &cameraY);
						if(checkCollision(player, true))
							player->moveRight(&cameraX, &cameraY, 200);
						break;
					case SDLK_d:
						player->moveRight(&cameraX, &cameraY, 200);
						if(checkCollision(player, true))
							player->moveLeft(&cameraX, &cameraY);
						break;
				}
			}
		}
		
		
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(mRenderer);
		
		map->render(mRenderer, cameraX, cameraY);
		player->render();
		
		for(int i = 0; i < mCharNum; i++)
		{
			characters[i]->cameraCX = cameraX;
			characters[i]->cameraCY = cameraY;
			characters[i]->render();
		}

		SDL_RenderPresent(mRenderer);
	}
}

void GameManager::loadMap(char *fileName, int x, int y)
{
	map.reset(new Map(mRenderer, x, y, fileName));
}

void GameManager::loadCharacters(char *playerName, char *fileName, int playerX, int playerY, int charNum)
{
	player.reset(new Player(playerName, mRenderer));
	player->mX = playerX;
	player->mY = playerY;
	
	mCharNum = charNum;
	
	characters.resize(mCharNum);
	
	std::ifstream file(fileName);
	std::string str;
	
	int y = 0;
	
	while(std::getline(file, str))
	{
		std::istringstream line(str);
		int i = 0;
		for(std::string each; std::getline(line, each, ','); i++)
		{
			switch(i)
			{
				case 0:
					characters[y].reset(new Character(each.c_str(), mRenderer));
					break;
				case 1:
					characters[y]->name = each;
					break;
				case 2:
					characters[y]->mX = stoi(each);
					break;
				case 3:
					characters[y]->mY = stoi(each);
					break;
			}
			
			
		}
		
		y++;
	}
	
	file.close();
}

bool GameManager::checkCollision(std::shared_ptr<Character>chr, bool player)
{
	bool colliding = false;
	
	//check with characters
	for(int i = 0; i < mCharNum; i++)
	{
		if(player)
		{
			if((chr->mX + cameraX) < (characters[i]->mX + 30) && (chr->mX + cameraX + 30) > characters[i]->mX)
			{
				if((chr->mY + cameraY) < (characters[i]->mY + 50) && (chr->mY + cameraY + 50) > characters[i]->mY)
					colliding = true;
			}
		}
		else
		{
			if(chr->mX < (characters[i]->mX + 30) && (chr->mX + 30) > characters[i]->mX)
			{
				if(chr->mY < (characters[i]->mY + 50) && (chr->mY + 50) > characters[i]->mY)
					colliding = true;
			}
		}
	}
	
	//check with tiles
	
	if(player)
	{
		if(map->isColliding(((chr->mX + cameraX)/20), ((chr->mY + cameraY + 45)/20)) || map->isColliding(((chr->mX + cameraX + 25)/20), ((chr->mY + cameraY + 45)/20)))
			colliding = true;
	}
	else
	{
		if(map->isColliding(((chr->mX)/20), ((chr->mY)/20)))
			colliding = true;
	}
	
	return colliding;
}
