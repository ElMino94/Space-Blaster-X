#pragma once
#ifndef MOB_H
#define MOB_H
#include"projectile.h"
#include"player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
class Player;
class Mob
{
protected:

    int pv;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float acceleration;
    float friction;
    std::vector<Projectile> projectiles;
    float attackCooldown;
    float attackTimer;

public:
    Texture texture;
    Sprite shipSprite;

    Mob(float x, float y, int hp, Texture texture);
    ~Mob() = default;

    bool isalive();
    void move(int dx, int dy);
    void takeDamage(int damage);

    virtual void attack(sf::Vector2f playerPosition);
    virtual void update(float deltaTime, sf::Vector2f playerPosition, std::vector<Mob>& mobs, sf::RenderWindow& window, Player& player);
    sf::FloatRect getBounds() const;
    sf::CircleShape ship;
};



#endif