#include"menu.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

MENU::MENU() {
    initialisation(); // Appel automatique pour charger textures/polices
}

// Méthode pour initialiser les textures, polices et sprites
void MENU::initialisation() {
    // Chargement des textures
    if (!backgroundTexture.loadFromFile("assetocorsa/image-fond-menu.jpg"))
        cerr << "Erreur : Impossible de charger l'image de fond !" << endl;

    if (!playTexture.loadFromFile("assetocorsa/bp.png"))
        cerr << "Erreur : Impossible de charger play.png !" << endl;

    if (!settingsTexture.loadFromFile("assetocorsa/set.png"))
        cerr << "Erreur : Impossible de charger set.png !" << endl;

    if (!exitTexture.loadFromFile("assetocorsa/ex.png"))
        cerr << "Erreur : Impossible de charger ex.png !" << endl;

    // Configuration des sprites
    backgroundSprite.setTexture(backgroundTexture);

    playSprite.setTexture(playTexture);
    playSprite.setPosition(50, 200);

    settingsSprite.setTexture(settingsTexture);
    settingsSprite.setPosition(50, 350);

    exitSprite.setTexture(exitTexture);
    exitSprite.setPosition(50, 500);

    // Chargement de la police et configuration du texte
    if (!font.loadFromFile("assetocorsa/Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return;
    }

    titleText.setFont(font);
    titleText.setString("Space Blaster X");
    titleText.setCharacterSize(75);
    titleText.setFillColor(Color(16, 39, 117));
    titleText.setStyle(Text::Bold | Text::Underlined);
    titleText.setPosition(50, 50);
}

// Affiche le menu principal
void MENU::drawMainMenu(RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(playSprite);
    window.draw(settingsSprite);
    window.draw(exitSprite);
}

// Affiche le menu des paramètres
void MENU::drawSettings(RenderWindow& window) {
    window.draw(backgroundSprite);

    Text settingsText;
    settingsText.setFont(font);
    settingsText.setString("Settings: Coming Soon...");
    settingsText.setCharacterSize(50);
    settingsText.setFillColor(Color::White);
    settingsText.setPosition(50, 300);

    window.draw(settingsText);
}

// Affiche un écran de confirmation pour quitter
void MENU::drawExitConfirmation(RenderWindow& window) {
    window.draw(backgroundSprite);

    Text exitText;
    exitText.setFont(font);
    exitText.setString("Are you sure you want to exit? (Y/N)");
    exitText.setCharacterSize(50);
    exitText.setFillColor(Color::White);
    exitText.setPosition(50, 300);

    window.draw(exitText);
}
