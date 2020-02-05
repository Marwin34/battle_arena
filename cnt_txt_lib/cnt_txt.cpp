#include "cnt_txt.hpp"

Counter::Counter(int red, int green, int blue, int charSize)
{

    font.loadFromFile("resources/font/arial.ttf");
    text.setString("0");
    text.setFont(font);
    text.setCharacterSize(charSize);
    color.r = red;
    color.g = green;
    color.b = blue;
    text.setFillColor(color);
}

void Counter::setCharSize(int charSize) { text.setCharacterSize(charSize); }

void Counter::setFillColor(int red, int green, int blue)
{
    color.r = red;
    color.g = green;
    color.b = blue;
    text.setFillColor(color);
}

void Counter::setPosition(int x, int y) { text.setPosition(x, y); }
void Counter::setValue(int value)
{
    std::string numberString = std::to_string(value);
    text.setString(numberString);
}

void Counter::draw(sf::RenderWindow* win) { win->draw(text); }

Text::Text(int red, int green, int blue, int charSize)
{
    font.loadFromFile("resources/font/signika.ttf");
    text.setString("NONE");
    text.setFont(font);
    text.setCharacterSize(charSize);
    color.r = red;
    color.g = green;
    color.b = blue;
    text.setFillColor(color);
}

void Text::setCharSize(int charSize) { text.setCharacterSize(charSize); }

void Text::setFillColor(int red, int green, int blue)
{
    color.r = red;
    color.g = green;
    color.b = blue;
    text.setFillColor(color);
}

void Text::setPositionAndValue(int x, int y, std::string textString)
{
    text.setPosition(x, y);
    text.setString(textString);
}

void Text::draw(sf::RenderWindow* win) { win->draw(text); }
