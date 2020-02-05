#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "cnt_txt_lib/cnt_txt.hpp"

#pragma once

class Button {
    int x;
    int y;
    int startX;
    bool terminateWindow;
    std::string action;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture hTexture;

public:
    Button();
    ~Button();
    void define(int, int, std::string);
    void checkClick(int, int, int&, int);
    void setPosition(int, int);
    void draw(sf::RenderWindow*);
};
