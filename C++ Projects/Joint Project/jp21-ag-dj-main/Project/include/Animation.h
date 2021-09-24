#pragma once
/// <summary>
/// NAMES
/// Davids and Adam
/// Platformer
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
    Animation curAnimation;
    void Init(int _pixelWidth, int _pixelHeight, int _numRows, int _numCols);
    void StartAnimation(Animation curAnimation);
    void nextFrame();

    sf::IntRect GetFrame();

private:
    sf::Vector2i frameSize{ };
    int numRows = 0;
    int numCols = 0;
    int curFrameOffset = 0;

    int frameCounter;

};