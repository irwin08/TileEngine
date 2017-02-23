#include "Player.h"
#include <iostream>


Player::Player(char *path, SDL_Renderer *renderer) : Character(path, renderer)
{

}

void Player::moveUp(int *cameraX, int *cameraY)
{
	if(*cameraY <= 0)
	{
		mY -= 5;
	}
	else
	{
		*cameraY -= 5;
	}
}

void Player::moveLeft(int *cameraX, int *cameraY)
{
	if(*cameraX <= 0)
	{
		mX -= 5;
	}
	else
	{
		*cameraX -= 5;
	}
}

void Player::moveRight(int *cameraX, int *cameraY, int width)
{
	//width = 200 for now
	if(mX < width)
	{
		mX += 5;
	}
	else
	{
		*cameraX += 5;
	}
}

void Player::moveDown(int *cameraX, int *cameraY, int height)
{
	//height = 200 for now
	if(mY < height)
	{
		mY += 5;
	}
	else
	{
		*cameraY += 5;
	}
}