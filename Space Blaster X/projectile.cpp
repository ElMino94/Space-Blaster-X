#include"projectile.h"


Projectile::Projectile(float x, float y, float angle, float speed, sf::Color color)
    : position(x, y), angle(angle), speed(speed), isMoving(false), timer(0.f)
{
    shape.setRadius(5.f);  // Taille du projectile
    shape.setFillColor(color);  // Couleur du projectile
    shape.setOrigin(shape.getRadius(), shape.getRadius());  // Centrer le projectile
    shape.setPosition(position);
}

void Projectile::update(float deltaTime) {
 
    float radianAngle = angle * 3.14159f / 180.f;  // Convertir l'angle en radians
    position.x += std::cos(radianAngle) * speed * deltaTime;  // Déplacement horizontal
    position.y += std::sin(radianAngle) * speed * deltaTime;  // Déplacement vertical

    shape.setPosition(position);  // Mettre à jour la position du projectile
    
}

void Projectile::render(sf::RenderWindow& window) {
    window.draw(shape);  // Dessiner le projectile
}

bool Projectile::isOutOfBounds(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect bounds = shape.getGlobalBounds();

    // Vérifier si le projectile est hors des limites de la fenêtre
    return bounds.left < 0 || bounds.top < 0 || bounds.left + bounds.width > windowSize.x || bounds.top + bounds.height > windowSize.y;
}
bool Projectile::checkCollision(const sf::FloatRect& mobBounds) {
    return shape.getGlobalBounds().intersects(mobBounds);
}