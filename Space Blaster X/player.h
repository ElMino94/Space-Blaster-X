#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

class Player
{
private:

    int pv;
    bool invincible;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float acceleration;
    float friction;
    int attaquespeed;

public:
    Texture pTexture;
    Sprite pSprite;
    Player(float x, float y);
    ~Player() = default;

    bool isalive();
    void move(float deltaTime);
    bool takedmg(int degat);

    void attack();
    void update(float deltaTime);

    
};



#endif