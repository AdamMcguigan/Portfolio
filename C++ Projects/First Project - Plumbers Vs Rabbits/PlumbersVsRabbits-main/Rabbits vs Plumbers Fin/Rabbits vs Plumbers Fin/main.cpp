
//Name of project: Rabbits game																								     
//Author: Adam Mcguigan																									     
//Date: 06-11-2020																											    
//Description: A turn base game, Fight your way through enemies in a strategic way and earn upgrades for your character	       
//Fight through 2 enemies and a boss after completing your fight with the enemies												  
//Time taken to compleate: 12 hours																	 


#include <iostream>			
#include "main.h"
using namespace std;

int main()
{
	int option = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(h, 9); cout << "                                                                                          \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                        \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                          \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                        \n  ";
	SetConsoleTextAttribute(h, 9); cout << "	_____ _           _              _____       _____     _   _    _ _\n";
	SetConsoleTextAttribute(h, 9); cout << "	| _  | |_ _ _____| |_ ___ ___   |  |  |___  |   __|___||_||_| _ ||____\n";
	SetConsoleTextAttribute(h, 9); cout << "	|  __| | | |     | . | -_ | _|  |  |  |_ -  |     |-  |  .| . |.||_|_-|\n";
	SetConsoleTextAttribute(h, 9); cout << "	|__| |_|___|_|_|_|___|__  _|     \___/|___| |__|__|__,|___|___|_|_||___|\n";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                          \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                        \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                          \n  ";
	SetConsoleTextAttribute(h, 9); cout << "                                                                                        \n  ";

	



	SetConsoleTextAttribute(h, 7);
	cout << "Welcome Player! its been a long time since we needed to call for your\n";
	cout << "help. Those Evil Rabbits have emerged from their demonic burrow\n";									//brief introduction to the game
	cout << "and we need your help 'removing' them again. we can run through\n ";
	cout << "how to defeat the rabbits again as its been to long since you last fought\n" << endl;

	cout << "Press '2' when your ready to progress" << std::endl;
	std::cin >> option;

	std::string move = "";

	int attack = 0;
	int attack2;
	int attack3;				//Variables used throughout 
	int coins = 0;
	int coinOption = 0;

	Plumber myPlumber;
	Enemy myGrunt;
	EnemyTwo myBrute;
	Boss BugsBunny;
	moreMoves myMoves;

	myPlumber.health = 100;
	myGrunt.health = 100;
	myGrunt.isGruntAlive = true;
	myPlumber.playerAlive = true;
	myPlumber.molotovs = 2;
	if (option == 2)
	{
		int playerSelection = 0;
		system("CLS");
		cout << "Which Character Do You Want To Play As ? \n" << endl;
		cout << "1.Sir Archibald, is fond of a splash of paddy in his coffee in the morning (mediocre Plumber) \n";
		cout << "2.Mr Whelan, rather fond of carrying bottles of jameson with him (questionable plumber, full time alcoholic)" << endl;
		cin >> playerSelection;


		if (playerSelection == 1)
		{
			system("CLS");
			cout << "You picked Sir Archibald - be sure not to speak to him before 3 in the afternoon" << endl;
			cout << endl;
		}
		else if (playerSelection == 2)
	    {
			system("CLS");
			cout << "You picked Mr Whelan - make sure your carrying some ginger ale" << endl;
			cout << endl;
		}

		cout << "Carefull! there's an evil rabbit over there\n";
		cout << "We need to move a bit closer before we can get rid of it for good\n";
		cout << "type in 'forward' to get closer to the evil rabbit\n";
		cin >> move;
		
		if (move == "forward")
		{
			system("CLS");
			cout << "The rabbit has noticed we're here, quickly get ready to massage its head with your weapon" << endl;
			myPlumber.move();
		}
		else
		{
			system("CLS");
			myGrunt.gruntMovement();
			cout << "The rabbit is getting closer, get ready!" << endl;
		}

		system("CLS");
		cout << "Player your health and attack options are listed below as well as enemy health\n";
		SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
		SetConsoleTextAttribute(h, 7); cout << "1.PVC Pipe\n";
		SetConsoleTextAttribute(h, 7); cout << "2.Heavy Pipe Wrench\n";
		SetConsoleTextAttribute(h, 7); cout << "3.Good Auld Molotov\n";
		SetConsoleTextAttribute(h, 7); cout << "4.Quench Your Thirst\n";
		SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << myGrunt.health << "-------------" << endl;
		cin >> attack;

		SetConsoleTextAttribute(h, 7);
		while (myGrunt.isGruntAlive == true)
		{

			switch (attack) {
			case 1:
				system("CLS");
				myGrunt.health = myPlumber.basicAttack(myGrunt.health);
				SetConsoleTextAttribute(h, 2);cout << "You cracked him on the head with your PVC Pipe, good job!" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 2:
				system("CLS");
				myGrunt.health = myPlumber.heavyAttack(myGrunt.health);
				SetConsoleTextAttribute(h, 2);cout << "You swung your pipe wrench, NOW THATS A LOT OF DAMAGE - Flex Seal Guy" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 3:
				if (myPlumber.molotovs > 0)
				{
					system("CLS");
					myGrunt.health = myPlumber.molotovAttack(myGrunt.health);
					SetConsoleTextAttribute(h, 2);cout << "You sacrifice one bottle of your whiskey, stuff it with a rag, light it and throw it and those evil rabbits" << endl;
					myPlumber.molotovs--;
					SetConsoleTextAttribute(h, 2);cout << " You Have:" << myPlumber.molotovs << " molotovs left" << std::endl;
					SetConsoleTextAttribute(h, 7);
					break;
				}

			case 4:
				system("CLS");
				myPlumber.health = myPlumber.heal(myPlumber.health);
				SetConsoleTextAttribute(h, 2);cout << "You took a swig from your bottle of whiskey, you gained 10 health and added to your drinking problem" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			default:
				while (attack < 0 || attack > 4)
				{
					cout << "Are you drunk while playing this ?, please select an attack " << endl;
					cin >> attack;
				}
			}
			if (myGrunt.health <= 0)
			{
				myGrunt.isGruntAlive = false;
				break;
			}

			int random = rand() % 4 + 1;

			if (random > 0 && random <= 3)
			{
				myPlumber.health = myGrunt.randomGruntAttack(random, myPlumber.health);
			}
			else
			{
				myGrunt.health = myGrunt.gruntHeal(myGrunt.health);
			}

			if (myPlumber.health <= 0)
			{
				system("CLS");
				SetConsoleTextAttribute(h, 4);cout << "YOU LOSE, GET GOOD BRO " << endl;
				SetConsoleTextAttribute(h, 7);
				exit(0);
			}


			cout << "Player your health and attack options are listed below as well as enemy health\n";
			SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
			SetConsoleTextAttribute(h, 7);
			cout << "1.PVC Pipe\n";
			cout << "2.Heavy Pipe Wrench\n";
			cout << "3.Good Auld Molotov\n";
			cout << "4.Quench Your Thirst\n";
			SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << myGrunt.health << "-------------" << endl;
			cin >> attack;
			SetConsoleTextAttribute(h, 7);
		}
		
		if (myGrunt.isGruntAlive == false)
		{
			coins = coins + 10;
			myPlumber.molotovs = 2;
		}


		if (coins >= 10)
		{
			system("CLS");
			cout << "Player those evil rabbits just dropped some coins after you defeated them" << endl;
			cout << "with these coins we can upgrade our movelist to use against the rabbits " << endl;
			cout << "Press '1' to upgrade " << endl;

		}

		
		std::cin >> coinOption;

		while (coinOption <= 0 || coinOption > 1)
		{
			system("CLS");
			cout << "Seriously!, u have to be drinking, please select a valid option" << endl;
			cin >> coinOption;
		}
		if (coinOption == 1)
		{
			system("CLS");
			cout << "Player you have recieved a new move!!, now we mow through those rabbits quicker" << endl;
		}


		///////////////////////////////////////////////////////// ENEMY TWO BELOW
		
		myBrute.isBruteAlive = true;
		myBrute.health = 100;
		myPlumber.health = 100;
		system("CLS");

		
		cout << "Damn we can never catch a whiskey break, another rabbit just appeared \n" << endl;
		cout << "Player your health and attack options are listed below as well as enemy health\n";
		SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
		SetConsoleTextAttribute(h, 7);
		cout << "1.PVC Pipe\n";
		cout << "2.Heavy Pipe Wrench\n";
		cout << "3.Good Auld Molotov\n";
		cout << "4.Quench Your Thirst\n";
		cout << "5.Whats better than One pipe Wrench.... Two pipe Wrenches" << endl;
		SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << myBrute.health << "-------------" << endl;
		cin >> attack2;
		myBrute.defence = myBrute.health + 1;
		SetConsoleTextAttribute(h, 7);
		while (myBrute.isBruteAlive == true)
		{

			switch (attack2) {
			case 1:
				system("CLS");
				myBrute.health = myPlumber.basicAttack(myBrute.health);
				SetConsoleTextAttribute(h, 2);cout << "You cracked him on the head with your PVC Pipe, good job!" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 2:
				system("CLS");
				myBrute.health = myPlumber.heavyAttack(myBrute.health);
				
				SetConsoleTextAttribute(h, 2);cout << "You swung your pipe wrench, NOW THATS A LOT OF DAMAGE - Flex Seal Guy" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 3:
				if (myPlumber.molotovs > 0)
				{
					system("CLS");
					myBrute.health = myPlumber.molotovAttack(myBrute.health);
					SetConsoleTextAttribute(h, 2);cout << "You sacrifice one bottle of your whiskey, stuff it with a rag, light it and throw it and those evil rabbits" << endl;
					myPlumber.molotovs--;
					SetConsoleTextAttribute(h, 2);cout << " You Have:" << myPlumber.molotovs << " Molotovs left" << std::endl;
					SetConsoleTextAttribute(h, 7);
					break;
				}
			case 4:
				system("CLS");
				myPlumber.health = myPlumber.heal(myPlumber.health);
				SetConsoleTextAttribute(h, 2);cout << "You took a swig from your bottle of whiskey, you gained 10 health and added to your drinking problem" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 5:
				system("CLS");
				myBrute.health = myMoves.specialMove(myBrute.health);
				//myPlumber.health = myPlumber.health + 12;  //////Comment this out to test
				SetConsoleTextAttribute(h, 2);cout << "You just crippled them filthy rabbits with Two pipe Wrenches, good job!" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			default:
				while (attack2 < 0 || attack2 > 5)
				{
					cout << "Really Bro, put down the bottle and choose a correct option " << endl;
					cin >> attack2;
				}
			}
			if (myBrute.health <= 0)
			{
				myBrute.isBruteAlive = false;
				break;
			}
			myBrute.defence;

			int random2 = rand() % 4 + 1;
			
			if (random2 > 0 && random2 <= 3)
			{
				myPlumber.health = myBrute.randomBruteAttack(random2, myPlumber.health);
			}
			else
			{
				myBrute.health = myBrute.bruteHeal(myBrute.health);
			}

			if (myPlumber.health <= 0)
			{
				system("CLS");
				SetConsoleTextAttribute(h, 4);cout << "YOU LOSE, GET GOOD BRO " << endl;
				SetConsoleTextAttribute(h, 7);
				exit(0);
			}


			cout << "Damn we can never catch a whiskey break, another rabbit just appeared \n" << endl;
			cout << "Player your health and attack options are listed below as well as enemy health\n";
			SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
			SetConsoleTextAttribute(h, 7);
			cout << "1.PVC Pipe\n";
			cout << "2.Heavy Pipe Wrench\n";
			cout << "3.Good Auld Molotov\n";
			cout << "4.Quench Your Thirst\n";
			cout << "5.Whats better than One pipe Wrench.... Two pipe Wrenches" << endl;
			SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << myBrute.health << "-------------" << endl;
			cin >> attack2;
			SetConsoleTextAttribute(h, 7);

		}
		
		//////////////////////////////////////////////////////////// BOSS BELOW
		
		system("CLS");
		cout << "FOR THE LOVE OF GOD, where are these rabbits coming from ??, i just want to have some whiskey" << endl;

		myPlumber.health = 100;
		BugsBunny.bossHealth = 150;
		BugsBunny.isBossAlive = true;


		
		cout << "Bugs Bunny has appeared, wearing Elmer fudds cap. Who knows what he done to him\n " << endl;
		cout << "Player your health and attack options are listed below as well as enemy health\n";
		SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
		SetConsoleTextAttribute(h, 7);
		cout << "1.PVC Pipe\n";
		cout << "2.Heavy Pipe Wrench\n";
		cout << "3.Good Auld Molotov\n";
		cout << "4.Quench Your Thirst\n";
		cout << "5.Whats better than One pipe Wrench.... Two pipe Wrenches" << endl;
		SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << BugsBunny.bossHealth << "-------------" << endl;
		cin >> attack3;
		SetConsoleTextAttribute(h, 7);
		while (BugsBunny.isBossAlive == true)
		{

			switch (attack3) {
			case 1:
				system("CLS");
				BugsBunny.bossHealth = myPlumber.basicAttack(BugsBunny.bossHealth);
				SetConsoleTextAttribute(h, 2);cout << "You cracked him on the head with your PVC Pipe, good job!" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 2:
				system("CLS");
				BugsBunny.bossHealth = myPlumber.heavyAttack(BugsBunny.bossHealth);
				SetConsoleTextAttribute(h, 2);cout << "You swung your pipe wrench, NOW THATS A LOT OF DAMAGE - Flex Seal Guy " << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 3:
				if (myPlumber.molotovs > 0)
				{
					system("CLS");
					BugsBunny.bossHealth = myPlumber.molotovAttack(BugsBunny.bossHealth);
					SetConsoleTextAttribute(h, 2);cout << "You sacrifice one bottle of your whiskey, stuff it with a rag, light it and throw it and those evil rabbits" << endl;
					myPlumber.molotovs--;
					SetConsoleTextAttribute(h, 2);cout << " You Have:" << myPlumber.molotovs << " Molotovs left" << std::endl;
					SetConsoleTextAttribute(h, 7);
					break;
				}
			case 4:
				system("CLS");
				myPlumber.health = myPlumber.heal(myPlumber.health);
				SetConsoleTextAttribute(h, 2);cout << "You took a swig from your bottle of whiskey, you gained 10 health and added to your drinking problem" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			case 5:
				system("CLS");
				BugsBunny.bossHealth = myMoves.specialMove(BugsBunny.bossHealth);
				//myPlumber.health = myPlumber.health + 12;
				SetConsoleTextAttribute(h, 2);cout << "You just crippled them filthy rabbits with Two pipe Wrenches, good job! and stole some health! \n" << endl;
				SetConsoleTextAttribute(h, 7);
				break;
			default:
				while (attack3 < 0 || attack3 > 5)
				{
					cout << "Stop drinking and select a valid option" << endl;
					cin >> attack3;
				}
			}
			
			if (BugsBunny.bossHealth <= 0)
			{
				BugsBunny.isBossAlive = false;
				break;
			}


			int random3 = rand() % 4 + 1;
			if (random3 > 0 && random3 <= 3)
			{
				myPlumber.health = BugsBunny.randomBossAttack(random3, myPlumber.health);
			}
			else
			{
				BugsBunny.bossHealth = BugsBunny.bossRegen(BugsBunny.bossHealth);
			}

			if (myPlumber.health <= 0)
			{
				system("CLS");
				SetConsoleTextAttribute(h, 4);cout << "YOU LOSE, GET GOOD BRO " << endl;
				SetConsoleTextAttribute(h, 7);
				exit(0);
			}

			cout << "Player your health and attack options are listed below as well as enemy health\n";
			SetConsoleTextAttribute(h, 2); cout << "-------------PLAYER HEALTH = " << myPlumber.health << "-------------" << endl;
			SetConsoleTextAttribute(h, 7);
			cout << "1.PVC Pipe\n";
			cout << "2.Heavy Pipe Wrench\n";
			cout << "3.Good Auld Molotov\n";
			cout << "4.Quench Your Thirst\n";//Quench Your Thirst
			cout << "5.Whats better than One pipe Wrench.... Two pipe Wrenches" << endl;
			SetConsoleTextAttribute(h, 4); cout << "-------------ENEMY HEALTH = " << BugsBunny.bossHealth << "-------------" << endl;
			cin >> attack3;
			SetConsoleTextAttribute(h, 7);


		}

		cout << "Congratulations, we finally did it, we beat all of those god damn rabbits " << endl;
		cout << "i think this means only one thing..... Whiskey time" << endl;
		cout << "press '1' to drink " << endl;
		int finaloption;
		std::cin >> finaloption;
		while (finaloption != 1)
		{
			system("CLS");
			cout << "Please Enter '1', the plumbers tongue is hanging out of his head for the want of whiskey " << endl;                                                  
			std::cin >> finaloption;
		}
		if (finaloption == 1)
		{
			system("CLS");
			SetConsoleTextAttribute(h, 2);
			cout << "Congratulations!!! you have 'removed' all of the rabbits that were plaguing this region " << endl;
			cout << "Everyone that lives here, thanks you from the bottom of their hearts " << endl;
			cout << "Most of all our plumbers are delighted to rid them evil rabbits so that they can spend " << endl;
			cout << "more time with the thing they love the most " << endl;
		}


	}
	return 0;
}
/*			 / \
		    / _ \
		   | / \ |
	       ||   ||   _______
		   ||   ||  |\     \
		   ||   ||  ||\     \
		   ||   ||  || \    |
		   ||   ||  ||  \__/
		   ||   ||  ||   ||
		    \\_ / \_ / \_//
		   /     _     _   \
		  /                 \
		  |      O     O    |
		  |     \  ___  /   |
		 /       \ \_/ /    \
		/    ---- - | ----   \
		|       \__/|\__ /    |
		\         |_|_|      /
		 \_____       ____ _/
				\     /
		        |     |  */																																								  																																									 