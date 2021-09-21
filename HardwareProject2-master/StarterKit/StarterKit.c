#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include <defines.h>
#include "StarterKit.h"
#include "data/font-6x12-full.inc"

#define FOLLOWER_TIME_INTERVAL 300

int rnd(int max);
void init();
void update();
void draw();
void MoveHero(int x, int y);
void drawRectangle(int x, int y, int width, int height, char c);
bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
		int width2, int height2);

static int heroX = 0;
static int heroY = 0;

static int heroWidth = 3;
static int heroHeight = 3;
static int enemyX = 0;
static float enemyY = 0;
static int enemyWidth = 3;
static int enemyHeight = 3;
static int wallX = 0;
static int wallY = 6;
static int wallHeight = 2;
static int wallWidth = 2;
static int moneyX = 5;
static int moneyY = 5;
static int moneyWidth = 2;
static int moneyHeight = 2;
static int followerX = 0;
static int followerY = 0;
static int followerWidth = 5;
static int followerHeight = 3;
static int followerThinkInterval = 300;
static int followerThinkTime = 0;
static int score = 0;
static int health = 6;
static int enemyHealth = 8;
static int moneyValue = 0;
static char kp;


//Controller Variables
static int buttonHeld = 0;
static int buttonPressed = 0;
static int buttonReleased = 0;
static int buttonPrevious = 0;

int main() {
	//Set font and tiles to be used, and call prior to ClearVram();
	SetFontTable(font);

	init(); // Initialise Game

	while (1) {
		WaitVsync(1);
		//Update the controller Variables
		buttonHeld = ReadJoypad(0);
		buttonPressed = buttonHeld & (buttonHeld ^ buttonPrevious);
		buttonReleased = buttonPrevious & (buttonHeld ^ buttonPrevious);
		update();
		draw();
	}
}

int rnd(int max) {
	int result = rand() % max;
	return result;
}

void init() {
	heroX = rnd(SCREEN_TILES_H);
	heroY = rnd(SCREEN_TILES_V);
	enemyY = 0;

	enemyX = rnd(SCREEN_TILES_V);
	followerY = rnd(SCREEN_TILES_V);
	followerX = rnd(SCREEN_TILES_H);
}

void update() {

	switch(buttonPressed){
		case BTN_UP:{
			MoveHero(0, -2);
			break;
		}
		case BTN_DOWN:{
			MoveHero(0, 2);
			break;
		}
		case BTN_LEFT:{
			MoveHero(-2, 0);
			break;
		}
		case BTN_RIGHT:{
			MoveHero(2, 0);
			break;
		}
		case BTN_A:{
		//If the A button is pressed increase the player size
			if(moneyValue >= 20)
			{
				heroWidth = 5;
			}
			break;
		}
		case BTN_B:{
			MoveHero(0, 2);
			break;
		}
		case BTN_X:{
			MoveHero(-2, 0);
			break;
		}
		case BTN_Y:{
			MoveHero(2, 0);
			break;
		}
		default:
			break;
	}


	buttonPrevious = buttonHeld;
	buttonPrevious = buttonHeld;

	followerThinkTime++;
	if (followerThinkTime > followerThinkInterval) {
		if (followerX < heroX)
			followerX++;
		if (followerX > heroX)
			followerX--;
		if (followerY < heroY)
			followerY++;
		if (followerY > heroY)
			followerY--;
		followerThinkTime = 0;
	}
	if (score > 5 && followerThinkInterval > 0) {
		followerThinkInterval--;
	}

	if (score == 0 && followerThinkInterval <= 0){
		followerThinkInterval = FOLLOWER_TIME_INTERVAL;
	}

	
		
	

	//write code to move the enemy down screen
	enemyY+= 0.15;
	//wallY++;
	
	// check if the enemy has reached the bottom of the screen
	if (enemyY >= SCREEN_TILES_V - enemyHeight) 
	{
		// reset enemy here..
		// to top of screen and a random y
		enemyX = rnd(SCREEN_TILES_H - enemyWidth);
		enemyY = 0;
	}
	if(wallY >= SCREEN_TILES_V - wallWidth)
	{
		wallX = rnd(SCREEN_TILES_H - enemyWidth);
		wallY = 0;
	}
	if (checkCollision(heroX, heroY, heroWidth, heroHeight, enemyX, enemyY,
			enemyWidth, enemyHeight) == true) {
		// write code to add score and reset enemy
		score = getScore(score, -1);
		//health = getHealth(health, -1);
		if(score <= 0 || score >= 254)
		{
			score = 0;
		}
		enemyX = rnd(SCREEN_TILES_H - enemyWidth);
		enemyY = 0;
	}

	if (checkCollision(heroX, heroY, heroWidth, heroHeight, followerX,
			followerY, followerWidth, followerHeight) == true) {
		// write code to add score and reset enemy
		//follower = the x rectangle
		//score = getScore(score, 1);
		health = getHealth(health, -1);
		if(score <= 0 )
		{
			score = 0;
		}
		followerX = rnd(SCREEN_TILES_H - followerWidth);
		followerY = 0;//rnd(SCREEN_TILES_V - wallHeight);
	}

	if(checkCollision(heroX,heroY,heroWidth,heroHeight,wallX
					,wallY,wallWidth,wallHeight) == true)
		{
			score = getScore(score,1);
			enemyHealth = getHealthEnemy(enemyHealth, -1);
			if(score <= 0)
			{
				score = 0;
			}
			if(enemyHealth <= 0 || enemyHealth >=230)
			{
				enemyHealth = 0;
			}
			wallX = rnd(SCREEN_TILES_V - wallWidth);
			wallY = rnd(SCREEN_TILES_V - wallHeight);
		}

	if(checkCollision(heroX,heroY,heroWidth,heroHeight,moneyX,
					moneyY,moneyWidth,moneyHeight) == true)
	{
		moneyValue = getMoney(moneyValue,2);
		if(moneyValue >= 100)
		{
			moneyValue = 100;
		}
		moneyX = rnd(SCREEN_TILES_V - moneyWidth);
		moneyY = rnd(SCREEN_TILES_H - moneyHeight);
	}		
	

	
	
		
	
}

void draw() 
{
	if(health <= 10)
	{

		//Clear the screen (fills Vram with tile zero)
		ClearVram();
		Print(1, 0, PSTR("Score"));
		Print(1, 17, PSTR("HEALTH"));
		Print(18, 17, PSTR("E.HP"));
		Print(1, 16, PSTR("MONEY"));
		PrintInt(11,16, moneyValue,false);
		PrintInt(10, 0, score, false);
		PrintInt(17, 0, heroX, false);
		PrintInt(22, 0, heroY, false);
		PrintInt(11, 17, health,false);
		PrintInt(30, 17, enemyHealth,false);
		drawRectangle(heroX, heroY, heroWidth, heroHeight, '0');
		drawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, '*');
		drawRectangle(followerX, followerY, followerWidth, followerHeight, 'X');
		drawRectangle(wallX,wallY,wallWidth,wallHeight, '?');
		drawRectangle(moneyX,moneyY,moneyWidth,moneyHeight,'$');
	}

	if(health == 0 || health >=235)
	{
		ClearVram();
		PrintChar(16,10,'Y');
		PrintChar(17,10,'O');
		PrintChar(18,10,'U');
		PrintChar(19,10,' ');
    	PrintChar(20,10,'L');
   		PrintChar(21,10,'O');
		PrintChar(22,10,'S');
		PrintChar(23,10,'E');
		health = 240;
	}

	if(score >= 8 && enemyHealth <=0)
	{
		ClearVram();
		PrintChar(16,10,'Y');
		PrintChar(17,10,'O');
		PrintChar(18,10,'U');
		PrintChar(19,10,' ');
    	PrintChar(20,10,'W');
   		PrintChar(21,10,'I');
		PrintChar(22,10,'N');
		score = 230;
	}
	
	
	
}

bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
		int width2, int height2) {
	// write the code to return true if collided.
	if (x1 + width1 < x2 || y1 + height1 < y2 || x1 > x2 + width2
			|| y1 > y2 + height2) {
		return false;
	} else {
		return true;
	}
}

void MoveHero(int x, int y) {
	// write code to move hero
	heroX = heroX + x;
	heroY = heroY + y;

	// write code to check if the hero is inside the window
	if (heroX < 0 || heroX + (TILE_WIDTH / heroWidth) >= SCREEN_TILES_H || heroY < 0
			|| heroY + (TILE_HEIGHT / heroWidth) >= SCREEN_TILES_V ) {
		heroX = heroX - x;
		heroY = heroY - y;
	}
}

void drawRectangle(int x, int y, int width, int height, char c) {
	if (x < SCREEN_TILES_H && y < SCREEN_TILES_V) {

		for (int i = 0; i < width; i++) {
			if (x + i < SCREEN_TILES_H && y < SCREEN_TILES_V) {
				PrintChar(x + i, y, c);
			}
			if (y + height - 1 < SCREEN_TILES_V) {
				PrintChar(x + i, y + height - 1, c);
			}
		}
		for (int i = 1; i < height; i++) {
			PrintChar(x, y + i, c);
			PrintChar(x + width - 1, y + i, c);
		}
	}
}
