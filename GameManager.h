#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"

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
		
		void shoot(int x, int y, int direction);
	
		std::vector<std::shared_ptr<Character>> characters;
		std::shared_ptr<Player> player;	
		std::shared_ptr<Map> map;

	private:
		
		bool checkCollision(std::shared_ptr<Character>chr, bool player);
		
		int cameraX;
		int cameraY;
		
		//checks to see if the player would like to quit, if not it keeps the game loop running
		bool quit;
		
		//keeps track of players life status
		bool dead;
		
		//tracks whether or not the game is paused
		bool pause;
		
		//number of characters in characters vector
		int mCharNum;

		std::vector<std::shared_ptr<Character>> bullets;
		std::vector<bool> bulletStatus;
		
		//pointer to the renderer
		SDL_Renderer *mRenderer;
};