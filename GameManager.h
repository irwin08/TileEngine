#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"
#include "Timer.h"

//GameManager class is what ties the pieces of the engine together.
//It contains the game loop, responds to user input and executes engine commands
class GameManager
{
	public:
	
		GameManager(SDL_Renderer *renderer);
	
		void loadMap(char *fileName, int x, int y);
		
		void loadCharacters(char *playerName, char *fileName, int playerX, int playerY, int charNum);
	
		void Start();
	
		void updateMap();
		
		void handleGraphics();
		
		void shoot(int x, int y, int direction);
		
		void handleKeyboardInput();
		
		void initBullets();
		
		void handleBullets();
		
		void aiCombat();
		
		void autoMove();
	
		std::vector<std::shared_ptr<Character>> characters;
		std::shared_ptr<Player> player;	
		std::shared_ptr<Map> map;

	private:
		
		
		
		
		bool checkCollision(std::shared_ptr<Character>chr, bool player);
		
		SDL_Event e;
		
		int cameraX;
		int cameraY;
		
		Timer fps;
		
		//checks to see if the player would like to quit, if not it keeps the game loop running
		bool quit;
		
		//keeps track of players life status
		bool dead;
		
		//tracks whether or not the game is paused
		bool pause;
		
		bool pKey;
		
		//number of characters in characters vector
		int mCharNum;

		std::vector<int> d2; //used as secondary direction if primary does not work
		
		std::vector<std::shared_ptr<Character>> bullets;
		bool bulletStatus[100];
		
		//pointer to the renderer
		SDL_Renderer *mRenderer;
};