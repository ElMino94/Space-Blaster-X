#include "player.h"
using namespace sf;
using namespace std;

Player::Player(float x, float y){
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 3750.f; // Vitesse de l'accélération
    friction = 0.975f; // Friction pour ralentir la vitesse
    invincible = false;
    pv = 100;
    attaquespeed = 1;
    pTexture.loadFromFile("assetocorsa\\player.png");
    pSprite.setTexture(pTexture);
}

bool Player::isalive(){

    return pv > 0;
}

void Player::move(float deltaTime) {
    Vector2f direction(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::Z))
        direction.y -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::S))
        direction.y += 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Q))
        direction.x -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::D))
        direction.x += 1.f;

    if (direction.x != 0.f || direction.y != 0.f) {
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
    }

    velocity += direction * acceleration * deltaTime;
    velocity *= friction;
    position += velocity * deltaTime;

    pSprite.setPosition(position);
}
bool Player::takedmg(int degat) {

    pv -= degat;
    if (pv <= 0) {
        pv = 0;
        return false;
    }
    return true;
}

void Player::attack() {}

void Player::update(float deltaTime) {

    Player::move(deltaTime);

}

