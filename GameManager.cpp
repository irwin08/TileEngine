#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Timer.h"

GameManager::GameManager(SDL_Renderer *renderer)
{
	cameraX = 0;
	cameraY = 0;
	mRenderer = renderer;
	quit = 0;
	distance = 0;
	noUpdate = 0;
	lastCheck = 0;
}

void GameManager::Start()
{
	SDL_Event e;
	
	int playerJumpValue = 15;
	
	const int FRAMES_PER_SECOND = 45;
	
	int frame = 0;
	bool cap = true;
	Timer fps;
	
	bool pause = false;
	
	bool pKey = false;
	
	srand(time(NULL));
	
	while(!quit)
	{

		fps.start();
		do
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
					quit = 1;
				/*else if(e.type == SDL_KEYDOWN)
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
						case SDLK_SPACE:
							player->jump(15);
							break;
					}
				}*/
			}
		
		
		
			const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
			
			/*if(currentKeyStates[SDL_SCANCODE_A])
			{
				player->moveLeft(&cameraX, &cameraY);
				if(checkCollision(player, true))
					player->moveRight(&cameraX, &cameraY, 200);
			}
			if(currentKeyStates[SDL_SCANCODE_D])
			{
				player->moveRight(&cameraX, &cameraY, 200);
				if(checkCollision(player, true))
					player->moveLeft(&cameraX, &cameraY);
			}*/
			if(currentKeyStates[SDL_SCANCODE_SPACE])
			{
				player->jump(15);
			}
			if(currentKeyStates[SDL_SCANCODE_P])
			{
				std::cout << pause << std::endl;
				pKey = true;
			}
			if(!currentKeyStates[SDL_SCANCODE_P] && pKey)
			{
				pause = !pause;
				if(pause == true)
					fps.pause();
				else
					fps.unpause();
				pKey = false;
			}
			
			if(quit)
				break;
		}while(pause);
		
		
		//force player right at v=1px/frame
		for(int i = 0; i < 3; i++)
		{
			player->moveRight(&cameraX, &cameraY, 200);
			if(checkCollision(player, true))
			{
				player->moveLeft(&cameraX, &cameraY);
				break;
			}
			distance++;
		}
		
		//make characters jump
		gravity(9);
		characterJump(player, true);
	
		
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(mRenderer);
		
		std::cout << cameraX << std::endl;
		
		//3760 is just a magic number for the end of the map
		if(cameraX > 3760)
			cameraX = 0;
		
		map->render(mRenderer, cameraX, cameraY);
		player->render();
			
		
		for(int i = 0; i < mCharNum; i++)
		{
			characters[i]->cameraCX = cameraX;
			characters[i]->cameraCY = cameraY;
			characters[i]->render();
		}

		SDL_RenderPresent(mRenderer);
		
		
		//update map
		
		//check to see if part of the map is offscreen so we can edit it
		if((distance - 500) > 0)
		{
			int i;
			if((((cameraX+200)/20)-20) < 0)
				i = 0;
			else
				i = (((cameraX+200)/20)-20);
			for(; i < (((cameraX+200)/20)-19); i++)
			{
				for(int j = 0; j < 25; j++)
				{
					if(!(map->getTileType(i, j) == 3))
						map->changeTileType(3, i, j);
				}
				noUpdate++;
			}
			
			if((distance - lastCheck) > 600)
			{
				lastCheck = distance;
				noUpdate = 0;
				
				int collumn = rand() % 5 + (((cameraX+200)/20)-25);
				
				int holeWidth = ((rand() % 10000 + 1000)/(cameraX+200))/20;
				
				if(holeWidth < 5)
					holeWidth = 5;
				if(holeWidth > 15)
					holeWidth = 15;
				
				int start = rand() % 25 - holeWidth;
				if(start < 0)
					start = 0;
				
				for(int k = 0; k < 25; k++)
				{
					map->changeTileType(4, collumn, k);
				}
				
				for(int k = 0; k < holeWidth; k++)
				{
					//std::cout << collumn << " " << start << std::endl;
					map->changeTileType(3, collumn, start);
					start++;
				}
				
			}
		}
		
		
		
		frame++;
		
		if((cap == true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
		
	}
}

void GameManager::loadMap(char *fileName, int x, int y)
{
	map.reset(new Map(mRenderer, x, y, fileName, true));
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
			if((chr->mX + cameraX) < (characters[i]->mX + 20) && (chr->mX + cameraX + 20) > characters[i]->mX)
			{
				if((chr->mY + cameraY) < (characters[i]->mY + 40) && (chr->mY + cameraY + 40) > characters[i]->mY)
					colliding = true;
			}
		}
		else
		{
			if(chr->mX < (characters[i]->mX + 20) && (chr->mX + 20) > characters[i]->mX && chr->name != characters[i]->name)
			{
				if(chr->mY < (characters[i]->mY + 40) && (chr->mY + 40) > characters[i]->mY)
				{
					colliding = true;
				}
			}
		}
	}
	
	//check with tiles
	
	if(player)
	{
		if(map->isColliding(((chr->mX + 1 + cameraX)/20), ((chr->mY + 1 + cameraY)/20)) || map->isColliding(((chr->mX + 19 + cameraX)/20), ((chr->mY + 1 + cameraY)/20)) || map->isColliding(((chr->mX + 1 + cameraX)/20), ((chr->mY + 39 + cameraY)/20)) || map->isColliding(((chr->mX + 19 + cameraX)/20), ((chr->mY + 39 + cameraY)/20)))
		{	
			colliding = true;
		}
	}
	else
	{
		if(map->isColliding(((chr->mX + 1)/20), ((chr->mY + 1)/20)) || map->isColliding(((chr->mX + 19)/20), ((chr->mY + 1)/20)) || map->isColliding(((chr->mX + 1)/20), ((chr->mY + 39)/20)) || map->isColliding(((chr->mX + 19)/20), ((chr->mY + 39)/20)))
		{
			colliding = true;
		}
	}
	
	return colliding;
}


void GameManager::gravity(int value)
{
	for(int i = 0; i < mCharNum; i++)
	{
		for(int j = 0; j < value; j++)
		{
			characters[i]->mY++;
			if(checkCollision(characters[i], false))
			{
				characters[i]->mY--;
				break;
			}
		}
	}
	
	for(int i = 0; i < value; i++)
	{
		player->mY++;
		if(checkCollision(player, true))
		{
			player->mY--;
			break;
		}
	}
}

void GameManager::characterJump(std::shared_ptr<Character> chr, bool isPlayer)
{
	if(chr->jumping)
	{
		if(chr->jumpingInterval < 15)
		{
			for(int i = 0; i < chr->jumpValue; i++)
			{
				chr->mY--;
				if(checkCollision(chr, isPlayer))
				{
					chr->mY++;
					chr->jumpingInterval = 15;
					break;
				}
			}
			
			
			
			
			chr->jumpingInterval++;
		}
		else
		{
			chr->jumpingInterval = 0;
			chr->jumping = false;
		}
	}
}
