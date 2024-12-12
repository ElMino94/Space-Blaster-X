#include "player.h"

Player::Player(float x, float y, int pv) : pv(pv){
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 3750.f; // Vitesse de l'acc�l�ration
    friction = 0.99925f; // Friction pour ralentir la vitesse
    invincible = false;
}

