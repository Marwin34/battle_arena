#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "button.hpp"
#include "cnt_txt_lib/cnt_txt.hpp"

#pragma once

class Gui {
    int mode;
    int gunsPosition;
    int scorePosition;
    int pointsPosition;
    int scorePosition2;
    int pointsPosition2;
    int delayCnt;
    int lastMapIndex;

    enum state {
        sScreen, // START
        rScreen, // RUNNING
        eScreen, // RESTART
        cScrren, // END
    };

    std::string scoreString;
    bool hSSaved;

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

    Counter ammuntion[6];

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
    void activeButtons(int, int, int, int&);
    void initialize(int, int);
    void switchState(int&);
    void updateWhilePlaying(int, int, int, int*, int, int, int);
    void loadHighScores();
    void saveHighScore(int);
    void resetHSflag();
    void draw(sf::RenderWindow*);
};
