#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <math.h>

#include "airdrop.hpp"

Airdrop::Airdrop() { }

Airdrop::Airdrop(int xx, int yy, int type, sf::Texture& text, sf::Texture& text2)
{
    x = xx;
    y = yy;

    toRemove = false;

    if (type >= 1)
        index = type - 1;

    kind = Type::AMMO;

    switch (type) {
    case 0:
        amount = (std::rand() % 50) + 75;
        kind = Type::MEDKIT;
        break;

    case 1:
        amount = (std::rand() % 30) + 20;
        break;

    case 2:
        amount = (std::rand() % 20) + 15;
        break;

    case 3:
        amount = (std::rand() % 30) + 20;
        break;

    case 4:
        amount = (std::rand() % 20) + 15;
        break;

    case 5:
        amount = (std::rand() % 15) + 1;
        break;

    case 6:
        amount = (std::rand() % 10) + 1;
        break;

    default:
        amount = 0;
        break;
    }

    if (kind == Type::MEDKIT)
        sprite.setTexture(text2);
    else
        sprite.setTexture(text);

    sprite.setPosition(x, y);
}

Airdrop::~Airdrop() { }

bool Airdrop::colliding(int boxX, int boxY, Player& player)
{
    float r = sqrt(pow(boxX - x, 2) + pow(boxY - y, 2));
    if (r < 20) {
        if (kind == Type::MEDKIT) {
            if (player.hp + amount > player.getMaxHp())
                player.hp = player.getMaxHp();
            else
                player.hp += amount;
        } else {
            player.ammunition[index] += amount;
        }

        return true;
    } else
        return false;
}

void Airdrop::update(sf::Time timer)
{
    if (repair) {
        y = (y / height) * height;
        repair = false;
    }

    if (timer.asMilliseconds() - lastUpdate.asMilliseconds() > 15) {

        if (!cDown) {
            g = 1;
            if (movePhase != fly)
                movePhase = fall;
        } else {
            g = 0;
            movePhase = stand;
            fallSpeed = 0;
        }
        if (movePhase == fall) {
            if (fallSpeed < FALL_SPEED_MAX)
                fallSpeed += g;
            if (cNext)
                fallSpeed = (y / height + 1) * height - y;
            y += fallSpeed;
        }

        cUp = false;
        cRight = false;
        cDown = false;
        cLeft = false;
        cNext = false;

        lastDir = dir;
        lastUpdate = timer;
        sprite.setPosition(x, y);

        if (y > 1000)
            toRemove = true;
    }
}

void Airdrop::draw(sf::RenderWindow* win) { win->draw(sprite); }
