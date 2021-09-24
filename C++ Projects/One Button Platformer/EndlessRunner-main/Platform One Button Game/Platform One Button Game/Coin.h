#pragma once
/// <summary>
/// Authors : Adam Mcguigan, Sasa Kuzmanovic, Sean Whelan
/// video link - https://instituteoftechnol663-my.sharepoint.com/:f:/g/personal/c00248515_itcarlow_ie/EkhpmSdezq1Jme-5xGJB2L0BqHBBIt6for7uCXcYwnCCzw?e=gqb42b
/// </summary>
#pragma once
#include "Animation.h"

class Coin
{
public:
	enum class CoinAnimationState { coinflip };
	CoinAnimationState animationState = CoinAnimationState::coinflip;
	Animation animations[1];
	AnimationSheet animSheet;
	sf::Vector2f position;
	sf::Sprite& spriteSheet;

	Coin(sf::Sprite& spheet) : spriteSheet(spheet)
	{

	}
	void InitAnimationData()
	{
		animations[int(CoinAnimationState::coinflip)] = { 4,0,15,true };

		animationState = CoinAnimationState::coinflip;
		animSheet.Init(spriteSheet.getGlobalBounds().width,
			spriteSheet.getGlobalBounds().height, 1, 4);
	}
	void startAnimaton(CoinAnimationState _animationState)
	{
		animationState = _animationState;
		animSheet.StartAnimation(animations[int(animationState)]);
	}
	void Draw(sf::RenderWindow& win)
	{
		animSheet.nextFrame();
		spriteSheet.setTextureRect(animSheet.GetFrame());
		win.draw(spriteSheet);
	}
	void Update()
	{



		if (animationState == CoinAnimationState::coinflip)
		{
			//std::cout << "Coin is flipping" << std::endl;
		}
	}
};