#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class MENU {
public:
	Texture ifmTexture;
	Texture bpTexture;
	Texture setTexture;
	Texture exTexture;	
	Sprite ifmSprite;
	Sprite bpSprite;
	Sprite setSprite;
	Sprite exSprite;
	void initialisation();//generation sprites
	void menu();//pause
	void ep(RenderWindow window);//first ecran
	void set();//settings
};

#endif