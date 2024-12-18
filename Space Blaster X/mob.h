#pragma once
#ifndef MOB_H
#define MOB_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class Mob
{
protected:

    int pv;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float acceleration;
    float friction;

public:
    Mob(float x, float y, int hp);
    ~Mob() = default;

    bool isalive();
    void move(int dx, int dy);
    bool takedmg(int degat);

    virtual void attack();
    virtual void update(float deltaTime, sf::Vector2f playerPosition, std::vector<Mob>& mobs, sf::RenderWindow& window);

    sf::CircleShape ship;

};



#endif