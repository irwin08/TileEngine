#include "Player.h"
#include <iostream>


Player::Player(char *path, SDL_Renderer *renderer) : Character(path, renderer)
{
	name = "Player";
}

void Player::moveUp(int *cameraX, int *cameraY)
{
	if(*cameraY <= 0)
	{
		mY -= 1;
	}
	else
	{
		*cameraY -= 1;
	}
}

void Player::moveLeft(int *cameraX, int *cameraY)
{
	if(*cameraX <= 0)
	{
		mX -= 1;
	}
	else
	{
		*cameraX -= 1;
	}
}

void Player::moveRight(int *cameraX, int *cameraY, int width)
{
	//width = 200 for now
	if(mX < width)
	{
		mX += 1;
	}
	else
	{
		*cameraX += 1;
	}
}

void Player::moveDown(int *cameraX, int *cameraY, int height)
{
	//height = 200 for now
	if(mY < height)
	{
		mY += 1;
	}
	else
	{
		*cameraY += 1;
	}
}