#include <SDL2/SDL.h>
#include <memory>

class Tile
{
	public:
		
		Tile(int type, SDL_Renderer *gRenderer);
		
		void render(SDL_Renderer *gRenderer, int x, int y);
		void changeType(int type);
		
		int getType();
		
		bool collidable;
		
	private:
		//number designating tile's texture and behaviour
		int mType;
		
		SDL_Texture *mTexture;
		SDL_Renderer *mRenderer;
		
		
		//looks at current type and loads a texture based on said type
		void setTexture();
		SDL_Texture *loadTexture(char *path);
		
};


