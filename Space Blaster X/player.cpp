#include "player.h"
using namespace sf;
using namespace std;

Player::Player(float x, float y){
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 3500.f; 
    friction = 0.975f; 
    invincible = false;
    pv = 100;
    attaquespeed = 1;
    currentAngle = 0.f;  
    rotationSpeed = 3.f;

    pTexture.loadFromFile("assetocorsa\\player.png");
    pSprite.setTexture(pTexture);
    pSprite.setScale(Vector2f(0.5, 0.5));
    pSprite.setOrigin(pTexture.getSize().x / 2.f, pTexture.getSize().y / 2.f);
}

void Player::move(float deltaTime, RenderWindow& window) {
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

    Vector2u windowSize = window.getSize();
    float spriteHalfWidth = pSprite.getGlobalBounds().width / 2.f;
    float spriteHalfHeight = pSprite.getGlobalBounds().height / 2.f;

    if (position.x - spriteHalfWidth < 0.f) {
        position.x = spriteHalfWidth;
    }
    else if (position.x + spriteHalfWidth > windowSize.x) {
        position.x = windowSize.x - spriteHalfWidth;
    }

    if (position.y - spriteHalfHeight < 0.f) {
        position.y = spriteHalfHeight;
    }
    else if (position.y + spriteHalfHeight > windowSize.y) {
        position.y = windowSize.y - spriteHalfHeight;
    }

    pSprite.setPosition(position);
}

void Player::pivot(float deltaTime, RenderWindow& window) {
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

    float targetAngle = atan2(mouseWorldPos.y - position.y, mouseWorldPos.x - position.x) * 180.f / 3.14159f;
    float angleDifference = targetAngle - currentAngle;

    if (angleDifference > 180.f) {
        angleDifference -= 360.f;
    }
    else if (angleDifference < -180.f) {
        angleDifference += 360.f;
    }

    if (abs(angleDifference) > 0.1f) {  
        currentAngle += angleDifference * rotationSpeed * deltaTime;  
    }
    else {
        currentAngle = targetAngle;  
    }
    pSprite.setRotation(currentAngle+90);

}
bool Player::takedmg(int degat) {

    pv -= degat;
    if (pv <= 0) {
        pv = 0;
        return false;
    }
    return true;
}

bool Player::isalive() {

    return pv > 0;
}

void Player::attack() {}

void Player::update(float deltaTime, RenderWindow& window) {

    Player::move(deltaTime, window);
    Player::pivot(deltaTime, window);
}

sf::Vector2f Player::getPosition() const {
    return position;
}