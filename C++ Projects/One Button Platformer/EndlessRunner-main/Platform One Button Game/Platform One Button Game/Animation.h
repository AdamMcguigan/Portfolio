/// <summary>
/// Authors - Adam Mcguigan, Sean Whelan, Sasa Kuzmanovic
/// video link - https://instituteoftechnol663-my.sharepoint.com/:f:/g/personal/c00248515_itcarlow_ie/EkhpmSdezq1Jme-5xGJB2L0BqHBBIt6for7uCXcYwnCCzw?e=gqb42b
/// </summary>
#pragma once
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <SFML/Graphics.hpp>
#include <iostream>
class Animation {
public:
	int numframes;
	int startOffset;
	int speed;
	bool loop;
};

class AnimationSheet
{
public:
	int frameCounter;
	sf::Vector2i frameSize{ };
	int numRows = 0;
	int numCols = 0;
	Animation curAnimation;
	int curFrameOffset = 0;
	void Init(int _pixelWidth, int _pixelHeight, int _numRows, int _numCols)
	{
		numCols = _numCols;
		numRows = _numRows;
		frameSize.x = _pixelWidth / numCols;
		frameSize.y = _pixelHeight / numRows;
		curFrameOffset = 0;
	}
	sf::IntRect GetFrame()
	{
		int row = curFrameOffset / numCols;
		int col = curFrameOffset % numCols;
		sf::IntRect frameRectangle;
		frameRectangle.left = col * frameSize.x;
		frameRectangle.top = row * frameSize.y;
		frameRectangle.width = frameSize.x;
		frameRectangle.height = frameSize.y;
		return frameRectangle;
	}
	void StartAnimation(Animation curAnimation)
	{
		this->curAnimation = curAnimation;
		frameCounter = 0;
		curFrameOffset = curAnimation.startOffset;
	}

	void nextFrame()
	{
		if (frameCounter > curAnimation.speed)
		{
			frameCounter = 0;
			if (curFrameOffset >= curAnimation.startOffset + curAnimation.numframes - 1)
			{
				if (curAnimation.loop == true)
				{
					curFrameOffset = curAnimation.startOffset;
				}
				else {
					curFrameOffset = curAnimation.startOffset + curAnimation.numframes - 1;
				}
			}
			else {
				std::cout << curFrameOffset << std::endl;
				curFrameOffset++;
			}
		}
		else {
			frameCounter++;
		}
	}
};
