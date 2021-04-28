#include "enemy.h"
#include <string>

Enemy::Enemy(SDL_Renderer* renderer, int speed, int maxH, int maxV, string dir, string type, int startX, int startY)
{
	enemyMovement = speed; //set up in pixels to move left, right, up, or down
	maxHorizontalMovement = maxH; //maximun number of moves the enemy can make to the left or right. 
	maxVerticalMovement = maxV; //max number of moves the enemy can make to up or down. 

	currentDirection = dir; //this is the direction the enem is currently moving

	enemyType = type; //clockwise or counter-clockwise

	SDL_Surface* surface = IMG_Load("./Assets/enemy.png"); 
	texture = SDL_CreateTextureFromSurface(renderer, surface); 
	SDL_FreeSurface(surface); 

	posRect.x = startX; 
	posRect.y = startY; //starting positions.
	int w, h; 
	SDL_QueryTexture(texture, NULL, NULL, &w, &h); 
	posRect.w = w; 
	posRect.h = h; 

	lastTime = 0; //int used to hold the latest value of current time. 

}

void Enemy::Update(float deltaTime)
{
	//move once per 1/2 second - 1000= 1 sec. 
	//update current time to the latest time elapsed. 
	currentTime = SDL_GetTicks(); 

	if (currentTime > lastTime + 500)
	{

		if ((currentDirection == "left") && (horizontalCounter < maxHorizontalMovement))
		{
			posRect.x -= enemyMovement; //move enemy left 1 increment. 
			horizontalCounter++; 

			if (horizontalCounter >= maxHorizontalMovement)//if the enemy has moved it's alloted spaces left, check to see if it needs to move left or down. 
			{

				horizontalCounter = 0; //reset the enemy's horizontal movement counter to 0. '

				if (enemyType == "CW")//clockwise
				{
					currentDirection = "up"; 
				}
				else if (enemyType == "CCW")
				{
					currentDirection = "down"; 
				}

			}

		}else if ((currentDirection == "down") && (verticalCounter < maxVerticalMovement))
		{
			posRect.y += enemyMovement; 
			verticalCounter++;

			if (verticalCounter >= maxVerticalMovement)
			{
				verticalCounter = 0;

				if (enemyType == "CW")//clockwise
				{
					currentDirection = "left";
				}
				else if (enemyType == "CCW")
				{
					currentDirection = "right";
				}
			}

		}else if ((currentDirection == "right") && (horizontalCounter < maxHorizontalMovement))
		{
			posRect.x += enemyMovement; 
			horizontalCounter++; 

			if (horizontalCounter >= maxHorizontalMovement)//if the enemy has moved it's alloted spaces left, check to see if it needs to move left or down. 
			{

				horizontalCounter = 0; //reset the enemy's horizontal movement counter to 0. '

				if (enemyType == "CW")//clockwise
				{
					currentDirection = "down";
				}
				else if (enemyType == "CCW")
				{
					currentDirection = "up";
				}

			}

		}else if ((currentDirection == "up") && (verticalCounter < maxVerticalMovement))
		{
			posRect.y -= enemyMovement; 
			verticalCounter++; 

			if (verticalCounter >= maxVerticalMovement)
			{
				verticalCounter = 0;

				if (enemyType == "CW")//clockwise
				{
					currentDirection = "right";
				}
				else if (enemyType == "CCW")//counter. 
				{
					currentDirection = "left";
				}
			}
		}

		lastTime = currentTime; //update clock
		
	}
}
void Enemy::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &posRect); 
}
Enemy::~Enemy()
{
	//SDL_DestroyTexture(texture);
}