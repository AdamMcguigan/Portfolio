#include "Collectible.h"


Collectible::Collectible(sf::Sprite& spheet) : 
	spriteSheetRuby(spheet)
{
}
void Collectible::InitAnimationData()
{
	animationsForRuby[int(RubyAnimationState::ruby)] = { 4,0,10,true };

	animationStateRuby = RubyAnimationState::ruby;
	animSheetRuby.Init(spriteSheetRuby.getGlobalBounds().width,
	spriteSheetRuby.getGlobalBounds().height, 1, 4);

}
void Collectible::startAnimaton(RubyAnimationState t_animationStateRuby)
{
	animationStateRuby = t_animationStateRuby;
	animSheetRuby.StartAnimation(animationsForRuby[int(animationStateRuby)]);


}
void Collectible::drawRuby(sf::RenderWindow& win)
{
	animSheetRuby.nextFrame();
	spriteSheetRuby.setTextureRect(animSheetRuby.GetFrame());
	win.draw(spriteSheetRuby);

}
