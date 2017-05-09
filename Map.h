#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include "Tile.h"

#define TILE_W = 20
#define TILE_H = 20


class Map
{
	public:
		
		Map(SDL_Renderer *gRenderer, int x, int y, const char *filePath, bool edit=false, bool newMap=false);
		
		void render(SDL_Renderer *gRenderer, int x=0, int y=0);
		void renderOffset(SDL_Renderer *gRenderer, int x=0, int y=0, int m=0, int n=0);
		
		void loadMap(const char *filePath, SDL_Renderer *gRenderer);
		
		void saveMap();
		
		int getTileType(int x, int y);
		
		bool isColliding(int x, int y);
		
		void changeTileType(int t, int x, int y);
		
		std::string getFilePath();
		
		int getX();
		int getY();
		
		
		
	private:
		
		SDL_Texture *loadTexture(char *path, SDL_Renderer *mRenderer);
		
		int mX;
		int mY;
		
		int topLeftX;
		int topLeftY;
		
		bool mEdit;		
		
		std::string mFilePath;
		
		std::vector< std::vector<std::shared_ptr<Tile>> > tiles;
};


