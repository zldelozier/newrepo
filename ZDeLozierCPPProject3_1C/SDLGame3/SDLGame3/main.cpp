#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;

bool quit = false; 
float deltaTime = 0.0f; //frame rate
int thisTime = 0; 
int lastTime = 0; 

int playerMovement = 71; 
SDL_Rect playerPos; 

//NEW PATROLLING 1 ****************************************

#include "enemy.h"
#include <vector>
vector<Enemy> enemyList; 
//max num. of enemies. 
int numberOfEnemies; 
//NEW PATROLLING 1 END ************************************

//NEW INVENTORY 1****************************************

#include "coin.h"
vector<Coin> coinList; 
int numberOfCoins; 
int score = 0; 

Mix_Chunk* pickup; 

void PlayerHit() {
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (SDL_HasIntersection(&playerPos, &enemyList[i].posRect))
		{
			cout << "Player hit by enemy!!" << endl;
			cout << "You have lost!" << endl;

			break;
		}
	}
}

//NEW INVENTORY END ***********
int main(int argc, char* argv[])
{
	SDL_Window* window; 
	SDL_Renderer* renderer; 
	SDL_Surface* surface = IMG_Load("./Assets/level.png"); 
	window = SDL_CreateWindow(
		"Dungeon Crawler",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		642,
		358,
		SDL_WINDOW_OPENGL
	); 
	if (window == NULL)
	{
		printf("Could not open window %s\n", SDL_GetError()); 
		return 1; 
	}
	//create bkgd. 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	SDL_Texture* bkgd; 
	bkgd = SDL_CreateTextureFromSurface(renderer, surface); 
	SDL_FreeSurface(surface); 
	SDL_Rect bkgdPos; 
	bkgdPos.x = 0;
	bkgdPos.y = 0; 
	bkgdPos.w = 642; 
	bkgdPos.h = 358; 
	//end create bkgd. 
	//player create --- CREATE

	surface = IMG_Load("./Assets/player.png"); 
	SDL_Texture* player; 
	player = SDL_CreateTextureFromSurface(renderer, surface); 
	SDL_FreeSurface(surface); 
	playerPos.x = 291; 
	playerPos.y = 291; 
	playerPos.w = 59; 
	playerPos.h = 59; 

	//PLAYER CREATE -- END; 
	SDL_Event event; 

	const int mazeWidth = 9;
	const int mazeHeight = 5; 
	string maze[mazeHeight][mazeWidth] = {
		{"O","O","O","O","O","O","O","O", "O"},
		{"O","W","O","W","W","W","O","W", "O"},
		{"O","O","O","O","W","O","O","O", "O"},
		{"O","W","O","W","W","W","O","W","O"},
		{"O","O","O","O","P","O","O","O", "O"}
	};
	//player starts maze at row 5 col. 5; maze[4][4]
	int playerHorizontal = 4; 
	int playerVertical = 4; 

	//NEW PATROLLING 2 *********************************************

	enemyList.clear(); 

	numberOfEnemies = 4; 

	Enemy tempEnemy(renderer, 71, 2, 2, "left", "CCW", 575, 7); 

	enemyList.push_back(tempEnemy); 

	Enemy tempEnemy2(renderer, 71, 2, 2, "right", "CW", 7, 7);

	enemyList.push_back(tempEnemy2); 

	Enemy tempEnemy3(renderer, 71, 2, 2, "right", "CW", 433, 149);

	enemyList.push_back(tempEnemy3);

	Enemy tempEnemy4(renderer, 71, 2, 2, "up", "CCW", 149, 291);

	enemyList.push_back(tempEnemy4);

	//NEW PATROLING 2 - END ******************************************

	//NEW INVENTORY 2 **************************************

	coinList.clear(); 
	numberOfCoins = 4; 
	int totalCoins = 0; 


	Coin tempCoin(renderer, 18, 18); 
	coinList.push_back(tempCoin); 

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); 
	pickup = Mix_LoadWAV("./Assets/pickup.wav"); 

	Coin tempCoin2(renderer, 18, 302);
	coinList.push_back(tempCoin2);

	Coin tempCoin3(renderer, 586, 18);
	coinList.push_back(tempCoin3);

	Coin tempCoin4(renderer, 586, 302);
	coinList.push_back(tempCoin4);

	cout << "Score: " << score << endl; 




	while (!quit)
	{
		thisTime = SDL_GetTicks(); 
		deltaTime = (float)(thisTime - lastTime) / 1000; 
		lastTime = thisTime; 

		if (SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT)
			{
				quit = true; 
			}

			switch (event.type)
			{
			case SDL_KEYUP: 
				//UPDATE PLAYERPOS. 
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT: 

					//check to see if the player's potential hor. position is withcn the maze's right side limit. 
					if ((playerHorizontal + 1) < mazeWidth)
					{
						if (maze[playerVertical][playerHorizontal + 1] == "O")
						{

							//move the player in the maze array - set the future spot to "P"
							maze[playerVertical][playerHorizontal + 1] == "P"; 
							//move the open slot in the maze array - set the player's old spot to "O"
							maze[playerVertical][playerHorizontal] = "O"; 

							playerHorizontal += 1;
							//increase movement by 71 - move right. 
							playerPos.x += playerMovement;			
						}
					}

					break; 
				case SDLK_LEFT: 
					//check to see if the player's potential hor. position is withcn the maze's right side limit. 
					if ((playerHorizontal -1) >= 0)
					{
						if (maze[playerVertical][playerHorizontal -1] == "O")
						{

							//move the player in the maze array - set the future spot to "P"
							maze[playerVertical][playerHorizontal - 1] == "P";
							//move the open slot in the maze array - set the player's old spot to "O"
							maze[playerVertical][playerHorizontal] = "O";

							playerHorizontal -= 1;
							//decrease by 71 - move left. 
							playerPos.x -= playerMovement;
						}
					}
					break; 
				case SDLK_UP:
					//check to see if the player's potential hor. position is withcn the maze's right side limit. 
					if ((playerVertical - 1) >= 0)
					{
						if (maze[playerVertical -1][playerHorizontal] == "O")
						{

							//move the player in the maze array - set the future spot to "P"
							maze[playerVertical - 1][playerHorizontal] == "P";
							//move the open slot in the maze array - set the player's old spot to "O"
							maze[playerVertical][playerHorizontal] = "O";

							playerVertical -= 1;
							//decrese the player's pos by 71 - move up. 
							playerPos.y -= playerMovement;
						}
					}
					break;
				case SDLK_DOWN://works. 
					if (playerVertical + 1 < mazeHeight)
					{

						if (maze[playerVertical + 1][playerHorizontal] == "O")
						{
							//move the player in the maze array - set the future spot to "P"
							maze[playerVertical +1][playerHorizontal ] == "P";
							//move the open slot in the maze array - set the player's old spot to "O"
							maze[playerVertical][playerHorizontal] = "O";

							playerVertical += 1;
							playerPos.y += playerMovement;
						}
					}
					break;
				default: 
					break; 
				}//end of 2nd switch 

				break; 
			}//end of 1st switch 




		}

		//START UPDATE *******************************************************

		for (int i = 0; i < numberOfEnemies; i++)
		{
			enemyList[i].Update(deltaTime); 
		}


		for (int i = 0; i < numberOfEnemies; i++)
		{																	 
			if (SDL_HasIntersection(&playerPos, &enemyList[i].posRect))
			{
				cout << "Player hit by enemy!!" << endl;
				cout << "You have lost" << endl;
				break;
			}
		}

		//pickup coin. 
		for (int i = 0; i < coinList.size(); i++)
		{

			if (SDL_HasIntersection(&playerPos, &coinList[i].posRect))
			{

				coinList[i].RemoveFromScreen(); 

				Mix_PlayChannel(-1, pickup, 0); 

				totalCoins++; 
				//output temp. feedbacck. 
				cout << "Total Coins Found " << totalCoins << endl;
				score = totalCoins; 
				cout << "Score: " << score << endl;
				if (totalCoins == 4)
				{
					cout << "You have Won!" << endl; 
				}
			}

		}



		//START DRAW************************************************
		SDL_RenderClear(renderer); 
		SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos); 
		SDL_RenderCopy(renderer, player, NULL, &playerPos); 
		//draw coins 
		for (int i = 0; i < coinList.size(); i++)
		{
			coinList[i].Draw(renderer); 
		}

		//draw enemies. 
		for (int i = 0; i < enemyList.size(); i++)
		{
			enemyList[i].Draw(renderer); 
		}
		SDL_RenderPresent(renderer); 
	}//end game loop. 

	SDL_DestroyWindow(window); 
	SDL_Quit(); 
	return 0; 
}