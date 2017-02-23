#include "Character.h"

class Player : public Character
{
	public:
	
		Player(char *path, SDL_Renderer *renderer);
		
		void moveUp(int *cameraX, int *cameraY);
		void moveLeft(int *cameraX, int *cameraY);
		void moveRight(int *cameraX, int *cameraY, int width);
		void moveDown(int *cameraX, int *cameraY, int height);

	private:
	
};