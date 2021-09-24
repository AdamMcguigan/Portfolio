#pragma once
using namespace std;
#include <Windows.h>
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

class  baseCharacter		//making a public class
{
public:

	int defence;	 //making a defence variable

};

struct moreMoves
{
	virtual int specialMove(int& t_enemyhealth);
};

class Plumber : public baseCharacter						//making a class for the player while it inherites the base class 
{
public:													//public variables
	int health;										    //health variable
	int basicAttack(int& t_enemyhealth);				//making a void for the basic attack and passing an argument through it
	int heavyAttack(int& t_enemyhealth);				//making a void for the heavy attack and passing an argument through it
	int molotovAttack(int& t_enemyhealth);				//making a void for the molotov attack and passing an argument through it
	int heal(int& t_playerhealth);						//making a void for the heal and passing an argument through it 
	int molotovs;										//variable for the amount of molotovs the plumber will be allowed use
	bool playerAlive;									//bool for if the player is alive
	void move() { std::cout << "Well done player, you've progressed forward" << std::endl; }	//defining the void the player movement 
	
};

class Enemy : public baseCharacter									//making a class for the enemy while it inherites the basic class 
{
public:
	int health;															//health variable
	bool isGruntAlive;                                                  //bool for if the enemy is alive
	void gruntMovement() { std::cout << "Caution player, then enemy is coming our way" << std::endl; }    //defining the void the enemy movement
	int gruntHeal(int& t_heal);                                         //making a void for grunt heal while passing an argument 
	int randomGruntAttack(int t_num, int& t_health);                    //making a void for the random grunt attacks 
};

class EnemyTwo :public baseCharacter
{
public:
	int health;                                                      //health variable
	bool isBruteAlive;                                               //bool for if the enemy is alive
	int randomBruteAttack(int t_num, int& t_health);                 //making a void for the random Brute attacks 
	int bruteHeal(int& t_heal);                                      //making a void for Brute heal while passing an argument 

};

class Boss :public baseCharacter
{
public:
	int bossHealth;                                                 //health variable for the boss
	bool isBossAlive;                                               //bool for if the boss is alive
	int randomBossAttack(int t_num, int& t_health);					//random boss attacks that will be used later in the function setup
	int bossRegen(int& t_heal);										//Boss Regen - this will be used for giving the boss health back randomly throughout the fight 
};


int Plumber::basicAttack(int& t_enemyhealth)
{
	int damage;

	damage = t_enemyhealth - 7;
	t_enemyhealth = damage;

	return t_enemyhealth;
}

int Plumber::heavyAttack(int& t_enemyhealth)
{
	int damage;

	damage = t_enemyhealth - 14;
	t_enemyhealth = damage;
	return t_enemyhealth;
}

int Plumber::molotovAttack(int& t_enemyhealth)
{
	int damage;

	damage = t_enemyhealth - 12;
	t_enemyhealth = damage;
	return t_enemyhealth;
}

int Plumber::heal(int& t_playerhealth)
{
	int healplayer;

	healplayer = t_playerhealth + 10;
	t_playerhealth = healplayer;


	return t_playerhealth;
}

int Enemy::gruntHeal(int& t_heal)
{
	int enemyheal;

	enemyheal = t_heal + 3;
	t_heal = enemyheal;
	SetConsoleTextAttribute(h, 4); cout << "Those Pesky grunt rabbits just healed up" << endl;
	SetConsoleTextAttribute(h, 7);
	return t_heal;
}

int Enemy::randomGruntAttack(int t_num, int& t_health)
{
	int newPlayerHealth;
	if (t_num == 1)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy grunt rabbit just hit us with his carrot" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 7;
		t_health = newPlayerHealth;

	}
	if (t_num == 2)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy grunt just dropkicked us, good thing we have whiskey to numb the pain" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 10;
		t_health = newPlayerHealth;
	}
	if (t_num == 3)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy grunt threw acorns towards us in quick succession, get down!" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 9;
		t_health = newPlayerHealth;
	}

	return t_health;
}


int EnemyTwo::randomBruteAttack(int t_num, int& t_health)
{

	int newPlayerHealth;
	if (t_num == 1)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy brute rabbit just threw a slightly bigger carrot at us" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 8;
		t_health = newPlayerHealth;

	}
	if (t_num == 2)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy brute just headbutt, thats gonna hurt tomorrow " << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 11;
		t_health = newPlayerHealth;
	}
	if (t_num == 3)
	{
		SetConsoleTextAttribute(h, 4); cout << "Enemy brute is regurgitating his food and firing it at us" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 10;
		t_health = newPlayerHealth;
	}
	return t_health;
}

int EnemyTwo::bruteHeal(int& t_heal)
{
	int enemyheal;

	enemyheal = t_heal + 5;
	t_heal = enemyheal;
	SetConsoleTextAttribute(h, 4); cout << "Those brutes are healing up, be careful player!" << endl;
	SetConsoleTextAttribute(h, 7);
	return t_heal;
}

int Boss::randomBossAttack(int t_num, int& t_health)
{
	int newPlayerHealth;
	if (t_num == 1)
	{
		SetConsoleTextAttribute(h, 4); cout << "Bugs Bunny emerged with a hammer and just hit us with it, wheres Elmer Fudd when you need him? ohh wait i think he ate him \n" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 10;
		t_health = newPlayerHealth;

	}
	if (t_num == 2)
	{
		SetConsoleTextAttribute(h, 4); cout << "Bugs Bunny whipped out the revolver from his orchestra days and just shot at us" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 13;
		t_health = newPlayerHealth;
	}
	if (t_num == 3)
	{
		SetConsoleTextAttribute(h, 4); cout << "Bugs Bunny summoned Daffy Duck and Wile E. Coyote to throw dynamite at us" << endl;
		SetConsoleTextAttribute(h, 7);
		newPlayerHealth = t_health - 12;
		t_health = newPlayerHealth;
	}
	return t_health;
}

int Boss::bossRegen(int& t_heal)
{
	int enemyheal;
	enemyheal = t_heal + 10;
	t_heal = enemyheal;
	SetConsoleTextAttribute(h, 4); cout << "Hey! whats up Plumber? Bugs Bunny is healing up, get ready Player" << endl;
	SetConsoleTextAttribute(h, 7);
	return t_heal;
}


int moreMoves::specialMove(int& t_enemyhealth)
{

	int damage;

	damage = t_enemyhealth - 18;
	t_enemyhealth = damage;


	return t_enemyhealth;
}



//0 = Black       8 = Gray
//1 = Blue        9 = Light Blue
//2 = Green       A = Light Green
//3 = Aqua        B = Light Aqua
//4 = Red         C = Light Red
//5 = Purple      D = Light Purple
//6 = Yellow      E = Light Yellow
//7 = White       F = Bright White