#include <SDL2/SDL.h>
#include <string>

class Character
{
	public:
		
		Character(const char *path, SDL_Renderer *renderer);
		
		void render();
		
		void moveUp();
		void moveLeft();
		void moveRight();
		void moveDown();
		
		
		int mX;
		int mY;
		
		int w;
		int h;
		
		int cameraCX;
		int cameraCY;
		
		std::string name;
		
		void jump(int value);
		
		bool jumping;
		int jumpingInterval;
		int jumpValue;
	
		int correctValue;
	
	protected:
	
		//will need to implement sprite walking animations later, this is for that.
		bool walking;
		
		SDL_Texture *mTexture;
		SDL_Renderer *mRenderer;
		
		
		
		void loadTexture(const char *path);
	
};