#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;


class MENU {
public:

    MENU(); // Constructeur

    // Méthodes pour initialiser et dessiner différents écrans du menu
    void initialisation();       // Charger les textures, polices et positions
    void drawMainMenu(RenderWindow& window); // Affiche le menu principal
    void drawSettings(RenderWindow& window); // Affiche le menu des paramètres
    void drawExitConfirmation(RenderWindow& window); // Affiche un menu de confirmation de sortie

    Texture backgroundTexture;
    Sprite backgroundSprite;

    Texture playTexture;
    Sprite playSprite;

    Texture settingsTexture;
    Sprite settingsSprite;

    Texture exitTexture;
    Sprite exitSprite;

    Font font;
    Text titleText;
};

#endif