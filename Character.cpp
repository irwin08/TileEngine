#include "Character.h"
#include <iostream>

Character::Character(const char *path, SDL_Renderer *renderer, int width, int height)
{
	cameraCX = 0;
	cameraCY = 0;
	mRenderer = renderer;
	loadTexture(path);
	
	jumping = false;
	jumpingInterval = 0;
	jumpValue = 1;
	
	w = width;
	h = height;
	
	direction = 1;

	health = 10;
}

void Character::loadTexture(const char *path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *surface = SDL_LoadBMP(path);
	
	
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	
	newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	
	SDL_FreeSurface(surface);
	
	mTexture = newTexture;
}

void Character::render()
{	
	SDL_Rect rect;
	rect.x = mX - cameraCX;
	rect.y = mY - cameraCY;
	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(mRenderer, mTexture, NULL, &rect);
}

void Character::moveUp()
{
	mY -= 5;
}

void Character::moveLeft()
{
	mX -= 5;
}
		
void Character::moveRight()
{
	mX += 5;
}

void Character::moveDown()
{
	mY += 5;
}


void Character::jump(int value)
{
	jumping = true;
	jumpValue = value;
}

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		