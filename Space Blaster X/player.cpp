#include "player.h"

Player::Player(float x, float y){
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 3750.f; // Vitesse de l'accélération
    friction = 0.99925f; // Friction pour ralentir la vitesse
    invincible = false;
    pv = 100;
    attaquespeed = 1;
    pTexture.loadFromFile("assetocorsa\\player.png");
    pSprite.setTexture(pTexture);
}

bool Player::isalive(){}
void Player::move(float deltaTime) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
bool Player::takedmg(int degat) {}

void Player::attack() {}

void Player::update(float deltaTime) {

    Player::move(deltaTime);

}

