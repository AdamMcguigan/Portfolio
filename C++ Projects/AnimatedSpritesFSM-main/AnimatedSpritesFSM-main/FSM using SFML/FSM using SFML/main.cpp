//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "Animation.h"
//#include <chrono>
//#include <thread>
//#include <Windows.h>
//#include <string>
//#include "Events.h"
//
////0 = Black       8 = Gray
////1 = Blue        9 = Light Blue
////2 = Green       A = Light Green
////3 = Aqua        B = Light Aqua
////4 = Red         C = Light Red
////5 = Purple      D = Light Purple
////6 = Yellow      E = Light Yellow
////7 = White       F = Bright White
//
//
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Player FSM");
//
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	Animation fsm;
//	int i = 0;
//	int alive = 1;
//	string input = "";
//	sf::Texture playerTexture;
//
//	/*if (!playerTexture.loadFromFile())
//	{
//
//	}*/
//
//
//	while (alive == 1)
//	{
//		SetConsoleTextAttribute(h, 6);
//		std::cout << "Press 'w' to Pass the time || Press 'a' to Climb like spoderman || Press 'd' to jump like superman leaving earth \n" << std::endl;
//		SetConsoleTextAttribute(h, 4);
//		std::cout << "Press x to leave " << std::endl;
//		SetConsoleTextAttribute(h, 7);
//		std::cin >> input;
//
//
//		if (input == "w")
//		{
//			SetConsoleTextAttribute(h, 7);
//			fsm.idle();
//			//Sleep(1000);
//			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//			system("CLS");
//		}
//		if (input == "a")
//		{
//			SetConsoleTextAttribute(h, 7);
//			fsm.climbing();
//			//Sleep(1000);
//			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//			system("CLS");
//		}
//		if (input == "d")
//		{
//			SetConsoleTextAttribute(h, 7);
//			fsm.jumping();
//			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//			system("CLS");
//		}
//		if (input == "4")
//		{
//			SetConsoleTextAttribute(h, 7);
//			system("CLS");
//			std::cout << "Bro this is paid DLC, gimme some time to develope this feature " << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//			system("CLS");
//		}
//		if (input == "x")
//		{
//			exit(0);
//		}
//
//
//
//	}
//
//	return 0;
//}