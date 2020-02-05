#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <math.h>
#include <vector>

#include "bullet.hpp"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    spdX = 0;
    spdY = 0;
    width = 5;
    height = 5;
    ttl = 0;
    toRemove = false;

    lastUpdate = sf::Time::Zero;
}

Bullet::~Bullet() { }

void Bullet::create(
    int xx, int yy, float angle, std::string oName, sf::Texture& texture, int nDmg, int special)
{
    x = xx;
    y = yy;

    // SET SPEED
    spdX = sin(angle / 180 * PI) * SPEED;
    spdY = cos(angle / 180 * PI) * SPEED * (-1);

    dmg = nDmg;
    // SET ORIGIN
    originName = oName;

    sprite.setTexture(texture);
    sprite.setOrigin(1, 2);
    sprite.setPosition(x, y);
    sprite.setRotation(angle);
    if (special == 5)
        sprite.setScale(3, 3);
}

void Bullet::update(sf::Time timer)
{
    if (timer.asMilliseconds() - lastUpdate.asMilliseconds() > 20) {

        x += spdX * SPEED;
        y += spdY * SPEED;

        sprite.setPosition(x, y);

        lastUpdate = timer;
        ttl++;
    }
}

bool Bullet::colliding(int boxX, int boxY, int boxWidth, int boxHeight)
{
    // NORMALIZATION
    boxX *= BLOCK_SIZE;
    boxY *= BLOCK_SIZE;

    // COLLISION COUNTER
    int toTrue = 0;

    for (int i = 0; i < SPEED; i++) {
        if (x + spdX * i <= static_cast<float>(boxX) + static_cast<float>(boxWidth)
            && static_cast<float>(boxX) <= x + spdX * i + width
            && y + spdY * i + height <= static_cast<float>(boxY) + static_cast<float>(boxHeight)
            && static_cast<float>(boxY) <= y + spdY * i + height)
            toTrue++;
    }
    if (toTrue)
        return true;
    else
        return false;
}

void Bullet::draw(sf::RenderWindow* win) { win->draw(sprite); }
