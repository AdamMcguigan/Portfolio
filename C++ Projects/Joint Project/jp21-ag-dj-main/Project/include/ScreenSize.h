#pragma once
enum class MenuState { MENU, GAMEPLAY,INSTRUCTIONS, EXIT,CUSTOMIZATION };
enum class shipCustom {OLDSHIP, WARSHIP, SOYSHIP};
struct ScreenSize
{
public:
	static const int s_width{ 1440 };

	static const int s_height{ 900 };
};
