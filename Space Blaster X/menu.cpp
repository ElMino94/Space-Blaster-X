#include"menu.h"
using namespace sf;
using namespace std;

void initialisation()  
{
    Texture ifmTexture;
    Texture bpTexture;
    Texture setTexture;
    Texture exTexture;

    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    bpTexture.loadFromFile("assetocorsa\\bp.png");
    setTexture.loadFromFile("assetocorsa\\set.png");
    exTexture.loadFromFile("assetocorsa\\ex.png");

    Sprite ifmSprite(ifmTexture);
    ifmSprite.setPosition(0, 0);
    Sprite bpSprite(bpTexture);
    bpSprite.setPosition(50, 200);
    Sprite setSprite(setTexture);
    setSprite.setPosition(50, 350);
    Sprite exSprite(exTexture);
    exSprite.setPosition(50, 500);

    Font font;
    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return;
    }

    Text text;

    text.setFont(font);
    text.setString("Space Blaster X");
    text.setCharacterSize(75);
    text.setFillColor(Color(16, 39, 117));
    text.setStyle((Text::Bold | Text::Underlined));
    text.setPosition(50, 50);
}

void menu()
{
	





}

void ep() 
{
    

    
}
