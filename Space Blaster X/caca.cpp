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
int level = 1;
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
        menu.drawplay(window, level);
        for (auto& mob : mobs)
        {
            mob.update(deltaTime, player.getPosition(), mobs, window, player);
            window.draw(mob.shipSprite);
        }
        player.update(deltaTime, window, mobs);
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
    window.setFramerateLimit(60);

    MENU menu; 
    menu.initialisation();
    Texture texture;
    
    Player player(400.f, 300.f);
    mobs.push_back(Mob(200.f, 400.f, 100, texture));
    mobs.push_back(Mob(300.f, 400.f, 100, texture));
    mobs.push_back(Mob(400.f, 400.f, 100, texture));
    mobs.push_back(Mob(500.f, 400.f, 100, texture));
    mobs.push_back(Mob(000.f, 400.f, 100, texture));
    mobs.push_back(Mob(500.f, 400.f, 100, texture));
    mobs.push_back(Mob(500.f, 400.f, 100, texture));
    mobs.push_back(Mob(800.f, 400.f, 100, texture));
    mobs.push_back(Mob(600.f, 400.f, 100, texture));
    Clock clock;


    
    // Gestion des états du jeu
    GameState currentState = MODMENU;

    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;

        texture.loadFromFile("assetocorsa//ship.png");

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
