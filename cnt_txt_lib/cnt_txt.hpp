#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#pragma once

#define COUNTER_SIZE 35
#define TEXT_SIZE 35

class Counter {

    sf::Font font;
    sf::Text text;
    sf::Color color;

public:
    Counter(int = 255, int = 255, int = 255, int = COUNTER_SIZE);
    void setCharSize(int);
    void setFillColor(int, int, int);
    void setPosition(int, int);
    void setValue(int);
    void draw(sf::RenderWindow*);
};

class Text {

    sf::Font font;
    sf::Text text;
    sf::Color color;

public:
    Text(int = 255, int = 255, int = 255, int = TEXT_SIZE);
    void setCharSize(int);
    void setFillColor(int, int, int);
    void setPositionAndValue(int, int, std::string);
    void draw(sf::RenderWindow*);
};
