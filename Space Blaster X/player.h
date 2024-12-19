#ifndef PLAYER_H
#define PLAYER_H
#include"projectile.h"

#include"mob.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;
class Mob;
class Player
{
private:

    int pv;
    bool invincible;
    Vector2f position;
    Vector2f velocity;
    float acceleration;
    float friction;
    float attaquespeed;
    float attackTimer;
    float currentAngle;  
    float rotationSpeed;
    std::vector<Projectile> projectiles;
    int score;
    float maxSpeed;

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

    void attack(float deltaTime);
    void update(float deltaTime, RenderWindow& window, std::vector<Mob>& mobs);
    FloatRect getBounds() const;
    int getscore() const;
    
};



#endif