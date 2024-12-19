#include "player.h"
using namespace sf;
using namespace std;

Player::Player(float x, float y) {
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 2500.f;
    friction = 0.98f;
    invincible = false;
    pv = 100;
    attaquespeed = 0.5;
    attackTimer = 0.f;
    currentAngle = 0.f;
    rotationSpeed = 3.f;
    score = 0;

    maxSpeed = 1000.f;

    pTexture.loadFromFile("assetocorsa\\player.png");
    pSprite.setTexture(pTexture);
    pSprite.setScale(Vector2f(0.225, 0.225));
    pSprite.setOrigin(pTexture.getSize().x / 2.f, pTexture.getSize().y / 2.f);

    healthBar.setSize(Vector2f(100, 10));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(x, y - 20);
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

    float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > maxSpeed) {
        velocity = (velocity / speed) * maxSpeed; // Normaliser et appliquer la vitesse max
    }

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
    pSprite.setRotation(currentAngle + 90);

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

void Player::attack(float deltaTime) {
    attackTimer += deltaTime;
    if (Mouse::isButtonPressed(Mouse::Left) && attackTimer >= attaquespeed)
    {
        attackTimer = 0;
        float angle = currentAngle;  // L'angle de tir du joueur
        float speed = 1000;  // Vitesse du projectile
        sf::Color color = sf::Color::Green;  // Couleur du projectile

        // Cr er un nouveau projectile   la position actuelle du joueur
        projectiles.push_back(Projectile(position.x, position.y, angle, speed, color));
    }
}

void Player::update(float deltaTime, sf::RenderWindow& window, std::vector<Mob>& mobs) {
    Player::attack(deltaTime);
    Player::move(deltaTime, window);
    Player::pivot(deltaTime, window);

    
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        it->update(deltaTime);

        // V rifier la collision avec chaque mob
        bool projectileHit = false;
        for (auto& mob : mobs) {
            if (it->checkCollisionE(mob.getBounds())) {
                mob.takeDamage(100);  // Infliger des d g ts au mob
                projectileHit = true;
                score += 100;
                cout << score;
                break;
            }
        }

        // Si le projectile a touch  un mob, le retirer de la liste
        if (projectileHit) {
            it = projectiles.erase(it);  // Efface le projectile de la liste
        }
        else {
            it->render(window);  // Sinon, afficher le projectile
            ++it;  // Passer au prochain projectile
        }
    }

    for (auto it = mobs.begin(); it != mobs.end();) {
        // V rifiez si le mob est mort
        if (it->isalive() == false) {
            it = mobs.erase(it); // Supprimez le mob mort et obtenez un nouvel it rateur valide
        }
        else {
            ++it; // Passez au mob suivant
        }
    }
}

void Player::drawHealthBar(RenderWindow& window) {
    float healthRatio = pv / 100.f;  // Proportion de la vie restante (le joueur commence avec 100 points de vie)

    // Ajuster la taille de la barre de vie en fonction de la vie restante
    healthBar.setSize(Vector2f(100 * healthRatio, 10));

    // Changer la couleur de la barre de vie
    if (healthRatio > 0.6f) {
        healthBar.setFillColor(Color::Green);
    }
    else if (healthRatio > 0.3f) {
        healthBar.setFillColor(Color::Yellow);
    }
    else {
        healthBar.setFillColor(Color::Red);
    }

    // Dessiner la barre de vie au-dessus du joueur
    window.draw(healthBar);
}

Vector2f Player::getPosition() const {
    return position;
}

FloatRect Player::getBounds() const {
    return pSprite.getGlobalBounds();
}
int Player::getscore() const {
    return score;
}