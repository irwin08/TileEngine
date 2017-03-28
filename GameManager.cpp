#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Timer.h"
#include <thread>

//constructor, sets default variables for game
GameManager::GameManager(SDL_Renderer *renderer)
{
	cameraX = 0;
	cameraY = 0;
	mRenderer = renderer;
	quit = 0;
	//distance = 0;
	//noUpdate = 0;
	//lastCheck = 0;
	dead = false;
}

//function called to start game, contains game loop.
void GameManager::Start()
{
	SDL_Event e;
	
	//sets frame rate.
	const int FRAMES_PER_SECOND = 45;
	
	int frame = 0;
	bool cap = true;
	Timer fps;
	
	pause = false;
	
	//checks to see whether pause key 'P' has been pressed
	bool pKey = false;
	
	
	
	for(int i = 0; i < 100; i++)
	{
		bulletStatus[i] = false;
		bullets.resize(100);
		bullets[i].reset(new Character("characters/bullet.bmp", mRenderer, 1, 1));
	}
	
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
			
			if(currentKeyStates[SDL_SCANCODE_A])
			{
				player->direction = 0;
				
				for(int i = 0; i < 3; i++)
				{
					player->moveLeft(&cameraX, &cameraY);
					if(checkCollision(player, true))
					{
						player->moveRight(&cameraX, &cameraY, 200);
						break;
					}
				}
			}
			if(currentKeyStates[SDL_SCANCODE_D])
			{
				player->direction = 2;
				
				for(int i = 0; i < 3; i++)
				{
					player->moveRight(&cameraX, &cameraY, 200);
					if(checkCollision(player, true))
					{
						player->moveLeft(&cameraX, &cameraY);
						break;
					}
				}
			}
			if(currentKeyStates[SDL_SCANCODE_S])
			{
				player->direction = 3;
				
				for(int i = 0; i < 3; i++)
				{
					player->moveDown(&cameraX, &cameraY, 200);
					if(checkCollision(player, true))
					{
						player->moveUp(&cameraX, &cameraY);
						break;
					}
				}
			}
			if(currentKeyStates[SDL_SCANCODE_W])
			{
				player->direction = 1;
				
				for(int i = 0; i < 3; i++)
				{
					player->moveUp(&cameraX, &cameraY);
					if(checkCollision(player, true))
					{
						player->moveDown(&cameraX, &cameraY, 200);
						break;
					}
				}
			}
			if(currentKeyStates[SDL_SCANCODE_SPACE])
			{
				switch(player->direction)
				{
					case 0:
						//left
						shoot((player->mX - 1), player->mY, 0);
						break;
					case 1:
						//up
						shoot(player->mX, (player->mY - 1), 1);
						break;
					case 2:
						//right
						shoot((player->mX + player->w + 1), player->mY, 2);
						break;
					case 3:
						//down
						shoot(player->mX, (player->mY + player->h + 1), 3);
						break;
				}
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
	
		for(int c = 0; c < 5; c++)
		{
			
			//fire bullets
			for(int i = 0; i < 100; i++)
			{
				if(bulletStatus[i] == true)
				{
					switch(bullets[i]->direction)
					{
						case 0:
						//left
							bullets[i]->mX--;
							if(bullets[i]->mX <= 0)
							{
								bullets[i]->mX = 0;
								bulletStatus[i] = false;
							}
							break;
						case 1:
						//up
							bullets[i]->mY--;
							if(bullets[i]->mY <= 0)
							{
								bullets[i]->mY = 0;
								bulletStatus[i] = false;
							}
							break;
						case 2:
						//right
							bullets[i]->mX++;
							if(bullets[i]->mX >= ((20*map->getX()) - bullets[i]->w))
							{
								bullets[i]->mX = ((20*map->getX()) - bullets[i]->w);
								bulletStatus[i] = false;
							}
							break;
						case 3:
						//down
							bullets[i]->mY++;
							if(bullets[i]->mY >= ((20*map->getY()) - bullets[i]->h))
							{
								bullets[i]->mY = ((20*map->getY()) - bullets[i]->h);
								bulletStatus[i] = false;
							}
							break;
					}
					
					if(checkCollision(bullets[i], false))
					{
						for(int k = 0; k < mCharNum; k++)
						{
							if((bullets[i]->mX > characters[k]->mX) && (bullets[i]->mX < (characters[k]->mX + characters[k]->w)))
							{
								if((bullets[i]->mY > characters[k]->mY) && (bullets[i]->mY < (characters[k]->mX + characters[k]->w)))
								{
									//character hit
									characters[k]->health -= 3;
								}
							}
						}
						bulletStatus[i] = false;
					}
				}
			}
		}
	
		
		if(dead)
		{
			std::cout << "Game over" << std::endl;
			break;
		}
		
		for(int i = 0; i < mCharNum; i++)
		{
			if(characters[i]->health <= 0)
			{
				characters.erase(characters.begin() + i);
				mCharNum--;
				i--;
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
		
		for(int i = 0; i < 100; i++)
		{
			if(bulletStatus[i] == true)
			{
				bullets[i]->cameraCX = cameraX;
				bullets[i]->cameraCY = cameraY;
				bullets[i]->render();
			}
		}

		SDL_RenderPresent(mRenderer);
		
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
					characters[y].reset(new Character(each.c_str(), mRenderer, 20, 40));
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
			if(chr->mX < (characters[i]->mX + characters[i]->w) && (chr->mX + characters[i]->w) > characters[i]->mX && chr->name != characters[i]->name)
			{
				if(chr->mY < (characters[i]->mY + characters[i]->h) && (chr->mY + characters[i]->h) > characters[i]->mY)
				{
					colliding = true;
				}
			}
		}
	}
	
	//check with tiles
	
	if(player)
	{
		if(map->isColliding(((chr->mX + 1 + cameraX)/20), ((chr->mY + 1 + cameraY)/20)) || map->isColliding(((chr->mX + (chr->w - 1) + cameraX)/20), ((chr->mY + 1 + cameraY)/20)) || map->isColliding(((chr->mX + 1 + cameraX)/20), ((chr->mY + (chr->h - 1) + cameraY)/20)) || map->isColliding(((chr->mX + (chr->w - 1) + cameraX)/20), ((chr->mY + (chr->h - 1) + cameraY)/20)) || map->isColliding(((chr->mX + (chr->w/2) + cameraX)/20), ((chr->mY + (chr->h - 1) + cameraY)/20)) || map->isColliding(((chr->mX + (chr->w/2) + cameraX)/20), ((chr->mY + 1 + cameraY)/20)))
		{	
			colliding = true;
		}
	}
	else
	{
		if(map->isColliding(((chr->mX + 1)/20), ((chr->mY + 1)/20)) || map->isColliding(((chr->mX + (chr->w - 1))/20), ((chr->mY + 1)/20)) || map->isColliding(((chr->mX + 1)/20), ((chr->mY + (chr->h - 1))/20)) || map->isColliding(((chr->mX + (chr->w - 1))/20), ((chr->mY + (chr->h - 1))/20)))
		{
			colliding = true;
		}
	}
	
	return colliding;
}


void GameManager::shoot(int x, int y, int direction)
{
	//direction 0=left 1=up 2=right 3=down
	
	int index;
	
	for(int i = 0; i < 100; i++)
	{
		if(bulletStatus[i] == false)
			index = i;
	}
	
	bulletStatus[index] = true;
	
	bullets[index]->direction = direction;
	bullets[index]->mX = x;
	bullets[index]->mY = y;
}


