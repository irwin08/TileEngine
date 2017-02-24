#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"

class GameManager
{
	public:
	
		GameManager(SDL_Renderer *renderer);
	
		void loadMap(char *fileName, int x, int y);
		
		void loadCharacters(char *playerName, char *fileName, int playerX, int playerY, int charNum);
	
		void characterJump(std::shared_ptr<Character> chr, bool isPlayer);
	
		void Start();
	
		std::vector<std::shared_ptr<Character>> characters;
		std::shared_ptr<Player> player;	
		std::shared_ptr<Map> map;

	private:
		
		bool checkCollision(std::shared_ptr<Character>chr, bool player);
		
		void gravity(int value);
		
		int cameraX;
		int cameraY;
		
		bool quit;
		
		int mCharNum;
		
		SDL_Renderer *mRenderer;
};