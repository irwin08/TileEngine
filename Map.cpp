#include "Map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

Map::Map(SDL_Renderer *gRenderer, int x, int y, const char *filePath, bool edit, bool newMap)
{
	mEdit = edit;
	
	mX = x;
	mY = y;
	
	mFilePath = filePath;
	
	tiles.resize(mY);
	for(int i = 0; i < mY; i++)
	{
		tiles[i].resize(mX);
	}
	
	if(newMap == false)
	{
		loadMap(filePath, gRenderer);
	}
	else
	{
		for(int i = 0; i < mY; i++)
	{
		for(int j = 0; j < mX; j++)
		{
			tiles[i][j].reset(new Tile(3, gRenderer));
		}
	}
	}
}

void Map::render(SDL_Renderer *gRenderer, int x, int y)
{
	//since camerax and cameray are incrementing by 5, we have to divide by 5
	
	//topLeftX = x/20
	
	int k = 0;
	for(int i = k; i < mY; i++)
	{
		int l = 0;
		for(int j = l; j < mX; j++)
		{
			//to keep the proportions we must multiply x by 4 because x is going up by 5
			tiles[i][j]->render(gRenderer, ((j*20) - (x)), ((i*20) - (y)));
		}
		
	}
}

void Map::renderOffset(SDL_Renderer *gRenderer, int x, int y, int m, int n)
{
	//since camerax and cameray are incrementing by 5, we have to divide by 5
	
	//topLeftX = x/20
	
	int k = 0;
	for(int i = k; i < mY; i++)
	{
		int l = 0;
		for(int j = l; j < mX; j++)
		{
			tiles[i][j]->render(gRenderer, ((j*20) - (x) + m), ((i*20) - (y) + n));
		}
		
	}
}


void Map::loadMap(const char *filePath, SDL_Renderer *gRenderer)
{
	int y = 0;
	
	std::ifstream file(filePath);
	std::string str;
	
	//loading screen
	SDL_Texture *tex = loadTexture("graphics/loading.bmp", gRenderer);
	SDL_Rect rec;
	rec.x = 250;
	rec.y = 250;
	rec.w =	215;
	rec.h = 91;
	
	SDL_RenderCopy(gRenderer, tex, NULL, &rec);

	while(std::getline(file, str))
	{
		std::istringstream line(str);
		
			int i = 0;
		
			for(std::string each; std::getline(line, each, ','); i++)
			{
				tiles[y][i].reset(new Tile(atoi(each.c_str()), gRenderer));
			}

		y++;
	}
	file.close();
}

void Map::saveMap()
{
	std::ofstream file(mFilePath);
	for(int i = 0; i < mY; i++)
	{
		for(int j = 0; j < mX; j++)
		{
			file << tiles[i][j]->getType();
			if(j != mX)
				file << ',';
		}
		if(i != mY)
			file << '\n';
	}
	file.close();
}

int Map::getTileType(int x, int y)
{
	return tiles[y][x]->getType();
}


void Map::changeTileType(int t, int x, int y)
{
	if(!mEdit)
	{
		std::cout << "bug" << std::endl;
		return;
	}
	tiles[y][x]->changeType(t);
}


std::string Map::getFilePath()
{
	return mFilePath;
}


int Map::getX()
{
	return mX;
}
		
int Map::getY()
{
	return mY;
}


bool Map::isColliding(int x, int y)
{
	return tiles[y][x]->collidable;
}

SDL_Texture *Map::loadTexture(char *path, SDL_Renderer *mRenderer)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *surface = SDL_LoadBMP(path);
	
	newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	
	SDL_FreeSurface(surface);
	
	return newTexture;
}

	
	