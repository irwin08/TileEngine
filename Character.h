#include <SDL2/SDL.h>
#include <string>

//character class - holds data relevant to in game characters
class Character
{
	public:
		
		Character(const char *path, SDL_Renderer *renderer, int width=40, int height=20);
		
		void render();
		
		void moveUp();
		void moveLeft();
		void moveRight();
		void moveDown();
		
		//location on screen
		int mX;
		int mY;
		
		//width and height of character
		int w;
		int h;
		
		//orientation of character 0=left 1=up 2=right 3=down
		int direction;
		
		//camera location for character
		int cameraCX;
		int cameraCY;
		
		//unique name of character
		std::string name;
		
		void jump(int value);
		
		//values used by jump function to properly time it
		bool jumping;
		int jumpingInterval;
		int jumpValue;
	
		int health;
	
	protected:
	
		//will need to implement sprite walking animations later, this is for that.
		bool walking;
		
		//Pointers to necessary SDL values
		SDL_Texture *mTexture;
		SDL_Renderer *mRenderer;
		
		
		
		void loadTexture(const char *path);
	
};