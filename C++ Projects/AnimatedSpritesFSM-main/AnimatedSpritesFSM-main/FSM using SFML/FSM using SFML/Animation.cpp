#include "Animation.h"
#include "Climbing.h"
#include "Idle.h"
#include "Jumping.h"
#include "State.h"

Animation::Animation()
{
	// Loading all of the player Texture sheets for the different animations
	current = new Idle();
	if (!playerTextureSheet.loadFromFile("./images/idle.png")) 
	{
		totalElapsed = 0; animationframe = 0;
	}

	if (!playerWalkingRightSheet.loadFromFile("./images/RunRight.png"))
	{
		totalElapsed = 0; animationframe = 0;
	}

	if (!playerJumpingSheet.loadFromFile("./images/jump.png"))
	{
		totalElapsed = 0; animationframe = 0;
	}

	if (!playerWalkingLeftSheet.loadFromFile("./images/RunLeft.png"))
	{
		totalElapsed = 0; animationframe = 0;
	}

	if (!playerCheckDaggerIdleSheet.loadFromFile("./images/DaggerCheck.png"))
	{
		totalElapsed = 0; animationframe = 0;
	}

	if (!playerGlideSheet.loadFromFile("./images/Glide.png"))
	{
		totalElapsed = 0; animationframe = 0;
	}

	playerSprite.setTexture(playerTextureSheet);
	playerSprite.setPosition(50, 50);
	rectSourceSprite.height = 439;
	rectSourceSprite.width = 232;
	playerSprite.setTextureRect(rectSourceSprite);

}

void Animation::idle()
{
	current->idle(this);
}

void Animation::jumping()
{
	current->jumping(this);
}

void Animation::climbing()
{
	current->climbing(this);
}

// This is the Animated Idle function 
void Animation::idleAnimation()
{
	playerSprite.setTexture(playerTextureSheet);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 8)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 12)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.height = 439;
	rectSourceSprite.width = 232;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
}

// This is the Animated Jumping function 
void Animation::jumpingAnimation()
{
	playerSprite.setTexture(playerJumpingSheet);
	rectSourceSprite.height = 483;
	rectSourceSprite.width = 362;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 10)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);

}

// This is the Animated Walking Left function 
void Animation::walkingLeftAnimation()
{
	playerSprite.setTexture(playerWalkingLeftSheet);
	rectSourceSprite.height = 458;
	rectSourceSprite.width = 363;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 10)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
	playerSprite.move(-1, 0);
}

// This is the Animated Walking Right function 
void Animation::walkingRightAnimation()
{
	playerSprite.setTexture(playerWalkingRightSheet);
	rectSourceSprite.height = 458;
	rectSourceSprite.width = 363;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 9)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
	playerSprite.move(1, 0);
}

// This is the Animated Idle Dagger Check function 
void Animation::checkDaggerAnimation()
{
	playerSprite.setTexture(playerCheckDaggerIdleSheet);
	rectSourceSprite.height = 439;
	rectSourceSprite.width = 232;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 10)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
	
}

// This is the Animated glide function 
void Animation::glideAnimation()
{
	playerSprite.setTexture(playerGlideSheet);
	rectSourceSprite.height = 454;
	rectSourceSprite.width = 443;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 10)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
}

//This Function resets the player back to 50,50 and sets him back to idle
void Animation::reset()
{
	playerSprite.setPosition(50, 50);
	playerSprite.setTexture(playerTextureSheet);
	rectSourceSprite.height = 439;
	rectSourceSprite.width = 232;
	playerSprite.setTextureRect(rectSourceSprite);

	//Runs through the frames that i set up
	totalElapsed++;
	if (totalElapsed > 8)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 12)
		{
			animationframe = 0;
		}
	}
	int col = animationframe % 3;
	int row = animationframe / 4;
	rectSourceSprite.height = 439;
	rectSourceSprite.width = 232;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
}

