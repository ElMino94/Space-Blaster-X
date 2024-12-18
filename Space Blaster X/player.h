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
    Vector2f position;
    Vector2f velocity;
    float acceleration;
    float friction;
    int attaquespeed;
    float currentAngle;  
    float rotationSpeed;

public:


    Texture pTexture;
    Sprite pSprite;
    Player(float x, float y);
    ~Player() = default;
    Vector2f getPosition() const ;
    bool isalive();
    void move(float deltaTime, RenderWindow& window);
    void pivot(float deltaTime, RenderWindow& window);
    bool takedmg(int degat);

    void attack();
    void update(float deltaTime, RenderWindow& window);

    
};



#endif