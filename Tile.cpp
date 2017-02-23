#include "Tile.h"

Tile::Tile(int type, SDL_Renderer *gRenderer)
{
	mType = type;
	mRenderer = gRenderer;
	setTexture();
}

void Tile::render(SDL_Renderer *gRenderer, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 20;
	rect.h = 20;

	SDL_RenderCopy(gRenderer, mTexture, NULL, &rect);
}

void Tile::changeType(int type)
{
	mType = type;
	setTexture();
}

int Tile::getType()
{
	return mType;
}

void Tile::setTexture()
{
	switch(mType)
	{
		case 0:
			//grass
			mTexture = loadTexture("tiles/0.bmp");
			collidable = false;
			break;
		case 1:
			//water
			mTexture = loadTexture("tiles/1.bmp");
			collidable = true;
			break;
		case 2:
			//countertop
			mTexture = loadTexture("tiles/2.bmp");
			collidable = true;
			break;
		case 3:
			//walmartfloor
			mTexture = loadTexture("tiles/3.bmp");
			collidable = false;
			break;
		case 4:
			//shelftop
			mTexture = loadTexture("tiles/4.bmp");
			collidable = true;
			break;
		case 5:
			
		case 6:
			
		case 7:
			
		case 8:
			
		case 9:
		
		default:
			mTexture = loadTexture("tiles/0.bmp");
			break;
			
	}
}


SDL_Texture *Tile::loadTexture(char *path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *surface = SDL_LoadBMP(path);
	
	newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	
	SDL_FreeSurface(surface);
	
	return newTexture;
}


