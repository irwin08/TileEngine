#include "Character.h"
#include <iostream>

Character::Character(const char *path, SDL_Renderer *renderer)
{
	cameraCX = 0;
	cameraCY = 0;
	mRenderer = renderer;
	loadTexture(path);
	
	jumping = false;
	jumpingInterval = 0;
	jumpValue = 1;
	
	jumpCount = 0;
	
	correctValue = 0;
}

void Character::loadTexture(const char *path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *surface = SDL_LoadBMP(path);
	
	newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	
	SDL_FreeSurface(surface);
	
	mTexture = newTexture;
}

void Character::render()
{	
	SDL_Rect rect;
	rect.x = mX - cameraCX;
	rect.y = mY - cameraCY;
	rect.w = 20;
	rect.h = 40;

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

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		