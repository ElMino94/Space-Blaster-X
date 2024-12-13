#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
    Player(float x, float y);
    ~Player() = default;

    bool isalive();
    void move(int dx, int dy);
    bool takedmg(int degat);

    void attack();
    void update(float deltaTime);

    sf::CircleShape ship;

};



#endif