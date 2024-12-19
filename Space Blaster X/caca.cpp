#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "mob.h"
#include "menu.h"

using namespace std;
using namespace sf;

void cursor() {
    
}

vector<Mob> mobs;
//vector<Projectile> projectiles
enum GameState { MODMENU, PLAY, SETTINGS, EXIT };




void selmenu(RenderWindow& window, Player& player, MENU& menu, GameState& currentState, Event& event, float deltaTime) {

    Vector2f mousePos;

    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);

            if (currentState == MODMENU) {
                if (menu.playSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = PLAY;
                }
                else if (menu.settingsSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = SETTINGS;
                }
                else if (menu.exitSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = EXIT;
                }
            }
        }
    }

    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Escape) {
            currentState = EXIT;
        }
    }

    switch (currentState) {
    case MODMENU:
        menu.drawMainMenu(window);
        break;

    case PLAY:
        for (auto& mob : mobs)
        {
            mob.update(deltaTime, player.getPosition(), mobs, window);
            window.draw(mob.ship);
        }
        player.update(deltaTime, window);
        window.draw(player.pSprite);
        break;

    case SETTINGS:
        menu.drawSettings(window);
        break;

    case EXIT:
        window.close();
        break;
    }
}






int main()
{
    
    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(120);

    MENU menu; 
    menu.initialisation();

    Player player(400.f, 300.f);
    mobs.push_back(Mob(200.f, 400.f, 100));
    mobs.push_back(Mob(300.f, 400.f, 100));
    mobs.push_back(Mob(400.f, 400.f, 100));
    mobs.push_back(Mob(500.f, 400.f, 100));
    mobs.push_back(Mob(600.f, 400.f, 100));
    Clock clock;

    Texture pTexture;
    pTexture.loadFromFile("assetocorsa\\player.png");
    player.pSprite.setTexture(pTexture);

    
    
    // Gestion des états du jeu
    GameState currentState = MODMENU;

    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();

                selmenu(window, player, menu, currentState, event, deltaTime.asSeconds());
                                
            }
        }

        window.clear();

        selmenu(window, player, menu, currentState, event, deltaTime.asSeconds());

        window.display();
    }

        return 0;
}
