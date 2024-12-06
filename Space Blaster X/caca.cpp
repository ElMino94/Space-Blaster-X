#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

class Ennemi {
public:
    CircleShape taille;
    Vector2f moveEnnemi;

    Ennemi(float x, float y, CircleShape perso) {
        taille.setRadius(5);
        taille.setFillColor(Color(255, 255, 255, 128));
        taille.setOrigin(5, 5);
        taille.setPosition(x, y);
        Vector2f joueur(perso.getPosition().x, perso.getPosition().y);
        Vector2f direction = joueur - taille.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        moveEnnemi = direction / length * 2.0f;
    }

    void dep() {
        taille.move(moveEnnemi);
    }

    void draw(RenderWindow& window) {
        window.draw(taille);
    }

    bool sortieEcran(const int Largeur) const
    {
        return  taille.getPosition().x < 10 || taille.getPosition().x > Largeur - 10 ||
            taille.getPosition().y < 10 || taille.getPosition().y > Largeur - 10;
    }
};

class Mun {
public:
    CircleShape Muns;
    Vector2f moveMun;

    Mun(float rayon, Vector2f position, float angle, float speed) {
        Muns.setRadius(rayon);
        Muns.setFillColor(Color::Red);
        Muns.setPosition(position);
        Muns.setOrigin(rayon, rayon);
        moveMun.x = cos(angle) * speed;
        moveMun.y = sin(angle) * speed;
    }

    void move() {
        Muns.move(moveMun);
    }

    bool sortieEcran2(const int Largeur) const
    {
        return  Muns.getPosition().x < 10 || Muns.getPosition().x > Largeur - 10 ||
            Muns.getPosition().y < 10 || Muns.getPosition().y > Largeur - 10;
    }

    bool Collision(const Ennemi& ennemis) const
    {
        float distX = Muns.getPosition().x - ennemis.taille.getPosition().x;
        float distY = Muns.getPosition().y - ennemis.taille.getPosition().y;
        float distance = distX * distX + distY * distY;
        float Rayon = Muns.getRadius() + ennemis.taille.getRadius();
        return distance <= Rayon * Rayon;
    }
};

Vector2f Spawn(int Largeur) {
    int choix = rand() % 4;

    if (choix == 0) {
        return Vector2f(rand() % Largeur - 25, 25);
    }
    else if (choix == 1) {
        return Vector2f(rand() % Largeur - 25, Largeur - 25);
    }
    else if (choix == 2) {
        return Vector2f(11, rand() % Largeur - 25);
    }
    else {
        return Vector2f(Largeur - 25, rand() % Largeur - 25);
    }
}

int main() {
    const int Longueur = 900;
    const int Largeur = 600;

    RenderWindow window(VideoMode(Largeur, Longueur), "Tu vas mourir!!! T'es mort!!!! MOUAHAHAHAHAHAHahahahahaaaaaaaaaaaaaaaa");
    window.setFramerateLimit(60);

    RectangleShape rhaut(Vector2f(600, 30));
    rhaut.setFillColor(Color(0, 102, 102));
    rhaut.setPosition(0, 0);

    RectangleShape rbas(Vector2f(600, 330));
    rbas.setFillColor(Color(0, 102, 102));
    rbas.setPosition(0, 570);

    RectangleShape rgauche(Vector2f(30, 600));
    rgauche.setFillColor(Color(0, 102, 102));
    rgauche.setPosition(0, 0);

    RectangleShape rdroit(Vector2f(30, 600));
    rdroit.setFillColor(Color(0, 102, 102));
    rdroit.setPosition(570, 0);

    CircleShape clicg(40.f, 3);
    clicg.setFillColor(Color::Black);
    clicg.setPosition(230, 730);
    clicg.setRotation(270);
    clicg.setOrigin(40, 40);

    CircleShape clicd(40.f, 3);
    clicd.setFillColor(Color::Black);
    clicd.setPosition(370, 730);
    clicd.setRotation(90);
    clicd.setOrigin(40, 40);

    CircleShape clich(40.f, 3);
    clich.setFillColor(Color::Black);
    clich.setPosition(300, 660);
    clich.setOrigin(40, 40);

    CircleShape clicb(40.f, 3);
    clicb.setFillColor(Color::Black);
    clicb.setPosition(300, 800);
    clicb.setRotation(180);
    clicb.setOrigin(40, 40);

    CircleShape AA(30);
    AA.setFillColor(Color::Green);
    AA.setPosition(300, 730);
    AA.setOrigin(30, 30);

    RectangleShape fond(Vector2f(600, 900));
    fond.setFillColor(Color(64, 64, 64));
    fond.setPosition(0, 0);

    RectangleShape GameOver(Vector2f(540, 540));
    GameOver.setFillColor(Color::Black);
    GameOver.setPosition(30, 30);

    Text gameOverText;
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Game Over!\n\nAppuyez sur\n\nR : \trejouer\n\nEchap : quitter");
    gameOverText.setPosition(50, 50);

    // Perso
    bool Vivant = true;
    CircleShape Perso(10);
    float basex = Largeur / 2;
    float basey = Largeur / 2;
    Perso.setFillColor(Color::White);
    Perso.setOrigin(10.f, 10.f);
    Perso.setPosition(basex, basey);
    float moveSpeed = 2.0f;

    // Canon
    float angle = 0;
    RectangleShape Canon(Vector2f(10, 10));
    Canon.setFillColor(Color::Red);
    Canon.setOrigin(5.f, 0.f);
    Canon.setPosition(basex, basey);

    // Liste
    vector<Mun> Muns;
    vector<Ennemi> Ennemis;

    float Temps = 0.f;
    float Interval = 2.f;

    Clock clock;
    Clock Tire;
    Clock Score;

    bool shoot = false;
    bool canShoot = true;
    int nbSpawn = 1;

    float score = 0.f;
    int Bestscore = 0;

    bool invincible = false;
    bool mobile = true;
    Clock Tinvincible;

    Text commence;
    commence.setCharacterSize(30);
    commence.setFillColor(Color::White);
    commence.setString("  Cours petit!\n\n  Appuie sur 'R' \npour jouer, sinon \n'ECHAP' si tu es \n     un lache.");
    commence.setPosition(50, 150);

    enum class GameState {
        Menu,
        Playing,
        Exit
    };

    GameState state = GameState::Menu;


    while (state == GameState::Menu && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                state = GameState::Exit;
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            state = GameState::Playing;
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            state = GameState::Exit;
            window.close();
        }

        window.clear();
        window.draw(commence);
        window.draw(rhaut);
        window.draw(rbas);
        window.draw(rgauche);
        window.draw(rdroit);
        window.draw(clicg);
        window.draw(clicd);
        window.draw(clich);
        window.draw(clicb);
        window.draw(AA);
        window.display();
    }

    while (window.isOpen()) {
        Time Delai = clock.restart();
        Temps += Delai.asSeconds();
        Time Timescore = Score.restart();
        score += Timescore.asSeconds();
       


        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (mobile && Tinvincible.getElapsedTime().asSeconds() >= 4.0f) {
            invincible = true;
            mobile = false;
            Canon.setFillColor(Color::White);
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            Vivant = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Z) && Perso.getPosition().y > 40) {
            Perso.move(0, -moveSpeed);
            Canon.move(0, -moveSpeed);
            mobile = false;
            clich.setFillColor(Color(44, 48, 253));

        }
        if (Keyboard::isKeyPressed(Keyboard::S) && Perso.getPosition().y < Largeur - 40) {
            Perso.move(0, moveSpeed);
            Canon.move(0, moveSpeed);
            mobile = false;
            clicb.setFillColor(Color(44, 48, 253));
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) && Perso.getPosition().x > 40) {
            Perso.move(-moveSpeed, 0);
            Canon.move(-moveSpeed, 0);
            mobile = false;
            clicg.setFillColor(Color(44, 48, 253));
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && Perso.getPosition().x < Largeur - 40) {
            Perso.move(moveSpeed, 0);
            Canon.move(moveSpeed, 0);
            mobile = false;
            clicd.setFillColor(Color(44, 48, 253));
        }
        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            Vivant = true;
            Tinvincible.restart();
            Muns.clear();
            Ennemis.clear();
            Perso.setPosition(basex, basey);
            Canon.setPosition(basex, basey);
            Temps = 0.f;
            score = 0.f;
            nbSpawn = 1;
            shoot = false;
            canShoot = true;
            AA.setFillColor(Color::Green);
            invincible = false;
            mobile = true;
            Canon.setFillColor(Color::Red);
        }

        if (!Keyboard::isKeyPressed(Keyboard::Z)) {
            clich.setFillColor(Color::Black);
        }
        if (!Keyboard::isKeyPressed(Keyboard::S)) {
            clicb.setFillColor(Color::Black);
        }
        if (!Keyboard::isKeyPressed(Keyboard::Q)) {
            clicg.setFillColor(Color::Black);
        }
        if (!Keyboard::isKeyPressed(Keyboard::D)) {
            clicd.setFillColor(Color::Black);
        }

        Vector2i posSouris = Mouse::getPosition(window);
        Vector2f posCanon = Canon.getPosition();
        float deltaX = posSouris.x - posCanon.x;
        float deltaY = posSouris.y - posCanon.y;
        angle = atan2(deltaY, deltaX) * 180.f / 3.14159;
        Canon.setRotation(angle - 90.f);

        if (Mouse::isButtonPressed(Mouse::Left) && canShoot) {
            Tire.restart();
            shoot = true;
            canShoot = false;
        }
        if (Tire.getElapsedTime().asSeconds() < 2 && shoot) {
            float directionAngle = angle * 3.14159f / 180.f;
            Muns.push_back(Mun(4.f, posCanon, directionAngle, 4.f));
            AA.setFillColor(Color::Red);
        }
        if (Tire.getElapsedTime().asSeconds() >= 2 && Tire.getElapsedTime().asSeconds() <= 10 && shoot)
        {

        }
        if (Tire.getElapsedTime().asSeconds() > 10 && shoot)
        {
            shoot = false;
            canShoot = true;
            AA.setFillColor(Color::Green);
        }

        for (auto& Mun : Muns) {
            Mun.move();
        }

        for (auto& ennemi : Ennemis) {
            ennemi.dep();
        }

        if (Temps >= Interval) {
            if (!invincible)
            {
                Temps = 0.f;
                for (int i = 0; i < nbSpawn; ++i) {
                    Vector2f pos = Spawn(Largeur);
                    Ennemis.push_back(Ennemi(pos.x, pos.y, Perso));
                }
                nbSpawn += 3;
            }
            if (invincible)
            {
                Temps = 0.f;
                for (int i = 0; i < nbSpawn; ++i) {
                    Vector2f pos = Spawn(Largeur);
                    Ennemis.push_back(Ennemi(pos.x, pos.y, Perso));
                }
                nbSpawn += 100;
            }
        }

        for (auto mcol = Muns.begin(); mcol != Muns.end(); ) {
            bool colDet = false;
            for (auto ecol = Ennemis.begin(); ecol != Ennemis.end();) {
                if (mcol->Collision(*ecol)) {
                    ecol = Ennemis.erase(ecol);
                    mcol = Muns.erase(mcol);
                    colDet = true;
                    break;
                }
                else {
                    ++ecol;
                }
            }
            if (!colDet) {
                ++mcol;
            }
        }

        for (auto em = Ennemis.begin(); em != Ennemis.end(); ) {
            if (em->sortieEcran(Largeur)) {
                em = Ennemis.erase(em);
            }
            else {
                ++em;
            }
        }

        for (auto mm = Muns.begin(); mm != Muns.end(); ) {
            if (mm->sortieEcran2(Largeur)) {
                mm = Muns.erase(mm);
            }
            else {
                ++mm;
            }
        }

        int scoreA = static_cast<int>(round(score));
        Text scoreText;
        Text scoreHText;
        scoreText.setPosition(30, 20);
        scoreText.setCharacterSize(20);
        if (invincible)
        {
            if (Tinvincible.getElapsedTime().asSeconds() > 9.0f && Tinvincible.getElapsedTime().asSeconds() < 14.0f)
            {
                scoreText.setString("Hein??!");
            }
            if (Tinvincible.getElapsedTime().asSeconds() >= 14.0f)
            {
                scoreText.setString("WHOAAAAA C'EST BEAU ^^");
            }


        }
        else
        {
            scoreText.setString("Score: " + to_string(scoreA));
            scoreHText.setPosition(300, 20);
            scoreHText.setCharacterSize(20);
            scoreHText.setString("BEST Score: " + to_string(Bestscore));
        }

        for (const auto& ennemi : Ennemis) {
            if (!invincible)
            {
                Vector2f diff = ennemi.taille.getPosition() - Perso.getPosition();
                float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
                if (distance <= (ennemi.taille.getRadius() + Perso.getRadius()) && Vivant) {
                    if (scoreA > Bestscore)
                    {
                        Bestscore = scoreA;
                    }
                   
                    Vivant = false;
                }
            }
        }

        Muns.erase(remove_if(Muns.begin(), Muns.end(), [&](const Mun& mun)
            {
                return mun.sortieEcran2(Largeur);
            }
        ), Muns.end());

        Ennemis.erase(remove_if(Ennemis.begin(), Ennemis.end(), [&](const Ennemi& ennemi)
            {
                return ennemi.sortieEcran(Largeur);
            }
        ), Ennemis.end());

        if (!Vivant)
        {
            Muns.clear();
            Ennemis.clear();
            Perso.setPosition(basex, basey);
            Canon.setPosition(basex, basey);
            Temps = 0.f;
            score = 0.f;
            nbSpawn = 1;
            shoot = false;
            canShoot = true;
            AA.setFillColor(Color::Green);
            invincible = false;
            mobile = true;
            Canon.setFillColor(Color::Red);

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    return 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::R)) {
                    Vivant = true;
                    Tinvincible.restart();
                    return 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                    return 0;
                }
            }
        }



        window.clear();
        if (Vivant)
        {
            window.draw(fond);
            for (const auto& Ennemi : Ennemis) {
                window.draw(Ennemi.taille);
            }
            window.draw(Perso);
            window.draw(Canon);
            for (const auto& Mun : Muns) {
                window.draw(Mun.Muns);
            }
        }
        if (!Vivant)
        {
            window.draw(GameOver);
            window.draw(gameOverText);
        }
        window.draw(rhaut);
        window.draw(rbas);
        window.draw(rgauche);
        window.draw(rdroit);
        window.draw(clicg);
        window.draw(clicd);
        window.draw(clich);
        window.draw(clicb);
        window.draw(AA);
        if (Vivant)
        {
            window.draw(scoreText);
            window.draw(scoreHText);
        }
        window.display();
    }
    return 0;
}