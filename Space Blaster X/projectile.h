#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>

class Projectile {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float angle;      // Angle de tir du projectile
    float speed;      // Vitesse du projectile
    bool isMoving;    // Indique si le projectile a commencé à se déplacer
    float timer;      // Compteur pour l'attente de 0.5s

public:
    Projectile(float x, float y, float angle, float speed, sf::Color color);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    bool isOutOfBounds(sf::RenderWindow& window);  // Vérifie si le projectile est hors de l'écran
    bool checkCollision(const sf::FloatRect& mobBounds);


};

#endif
