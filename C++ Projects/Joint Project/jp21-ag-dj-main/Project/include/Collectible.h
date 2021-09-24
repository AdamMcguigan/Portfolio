#pragma once

#include "Animation.h"

class Collectible
{
public:
	enum class RubyAnimationState { ruby };

	sf::Sprite& spriteSheetRuby;

	Collectible(sf::Sprite& spheetCoin);
	void InitAnimationData();
	void startAnimaton(RubyAnimationState t_animationStateRuby);
	void drawRuby(sf::RenderWindow& win);

private:
	AnimationSheet animSheetRuby;
	Animation animationsForRuby[1];
	RubyAnimationState animationStateRuby = RubyAnimationState::ruby;

};