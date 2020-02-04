#include <iostream>
#include <fstream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "cnt_txt_lib/cnt_txt.hpp"
#include "button.hpp"

#pragma once

 class Gui{
    int mode;
    int gunsPosition;
    int scorePosition;
    int pointsPosition;
    int scorePosition2;
    int pointsPosition2;
    int delayCnt;
    int lastMapIndex;
    enum state{
        sScreen,//START
        rScreen,//DZIA£ANIE
        eScreen,//RESTART
        cScrren,//KONIEC
    };
    std::string scoreString;
    bool hSSaved;

    //OBRAZKI
    sf::Sprite guns[6];
    sf::Texture gunsTexture[6];
    sf::Image gunsImage;

    sf::Sprite playerHp;
    sf::Texture playerHpTexture;
    sf::Sprite playerHpBg;
    sf::Texture playerHpBgTexture;

    sf::Sprite startScreen;
    sf::Texture startTexture;

    sf::Sprite endScreen;
    sf::Texture endTexture;

    sf::Sprite completeScreen;
    sf::Texture completeTexture;

    sf::Sprite locked;
    sf::Texture lockedTexture;

    //sf::Music winS;
    //sf::Music loseS;

    Counter ammuntion[6];

    //WYŚWIETLANE NAPISY (LICZBOWE ORAZ LITEROWE)
    Text scores;
    Counter points;
    Text eScores;
    Counter ePoints;
    Text hScores;
    Text instruction;

    Button startButton;
    Button restartButton;
    Button quitButton;

    struct alert {
        Text name;
        Counter index;
        bool display;
    };

    alert mapName;

public:

    Gui();
    ~Gui();
    void setMode(std::string);
    void activeButtons(int,int,int,int&);
    void initialize(int,int);
    void switchState(int&);
    void updateWhilePlaying(int,int,int,int*,int,int,int);
    void loadHighScores(); // WCZYTYWANIE DANYCH Z PLIKU HS.TXT
    void saveHighScore(int);
    void resetHSflag();
    void draw(sf::RenderWindow*);
 };
