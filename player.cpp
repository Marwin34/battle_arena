#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "player.hpp"

Player::Player()
{

    x = 320;
    y = 500;

    frameX = 0;
    frameY = 2;

    g = 0;

    sCnt = 0;

    hp = 150;
    maxHp = hp;

    jumpSpeed = JUMP_SPEED;
    fallSpeed = 0;
    movePhase = fall;

    lastDir = none;
    dir = none;

    image.loadFromFile("resources/img/player2OLD.png");

    width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
    height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

    texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    lastUpdate = sf::Time::Zero;

    // COLLISION FLAGS
    cUp = false;
    cRight = false;
    cDown = false;
    cLeft = false;
    cNext = false;

    // BUTTON FLAGS
    Up = false;
    Right = false;
    Left = false;

    // SHOOT FLAG
    canFire = false;

    name = "HERO";

    weapon.define("glock", x + width / 2, y + height / 2);
    activeGun = 0;

    for (int i = 0; i < 6; i++) {
        if (i == 0)
            ammunition[i] = 40;
        if (i == 1)
            ammunition[i] = 25;
        if (i > 1)
            ammunition[i] = 99;
    }

    score = 0;
}

Player::~Player() { }

void Player::update(sf::Time timer, float angle, int mapWidth)
{
    if (repair) {
        y = (y / height) * height;
        repair = false;
    }

    if (timer.asMilliseconds() - lastUpdate.asMilliseconds() > 15) {
        chooseGun();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Right = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Left = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            Up = true;

        if (!cDown) {
            g = 1;
            if (movePhase != fly)
                movePhase = fall;
        } else {
            g = 0;
            movePhase = stand;
            jumpSpeed = JUMP_SPEED;
            fallSpeed = 0;
        }

        if (Right && !cRight && x < mapWidth - BLOCK_SIZE) {
            x += 4;
            dir = right;
        }
        if (Left && !cLeft && x > 0) {
            x -= 4;
            dir = left;
        }
        if (Left && Right)
            dir = none;

        if (Up && !cUp && movePhase == stand) {
            movePhase = fly;
        }
        if (movePhase == fly) {
            if (cUp) {
                movePhase = fall;
            } else {
                jumpSpeed -= g;
                if (jumpSpeed > 0) {
                    if (scUp)
                        jumpSpeed = y - y / 32 * 32;
                    y -= jumpSpeed;
                } else
                    movePhase = fall;
            }
        }
        if (movePhase == fall) {
            if (fallSpeed < FALL_SPEED_MAX)
                fallSpeed += g;
            if (cNext)
                fallSpeed = (y / height + 1) * height - y;
            y += fallSpeed;
        }

        if (movePhase == stand && !Left && !Right)
            dir = none;
        if (angle > 0)
            frameY = 2;
        else
            frameY = 1;
        if (dir == lastDir && dir != none)
            frameX++;
        else
            frameX = 0;
        if (movePhase == fall || movePhase == fly) {
            frameX = 4;
            dir = inAir;
        }
        if (frameX > 15)
            frameX = 0;
        texture.loadFromImage(
            image, sf::IntRect(frameX / 4 * width, frameY * height, width, height));

        cUp = false;
        cRight = false;
        cDown = false;
        cLeft = false;
        cNext = false;
        repair = false;
        Right = false;
        Left = false;
        Up = false;
        scUp = false;

        sCnt++;
        if (sCnt > weapon.getAttackSpeed()) {
            canFire = true;
        }

        weapon.update(x + width / 2, y + height / 2, angle);

        lastDir = dir;

        lastUpdate = timer;
        sprite.setPosition(x, y);
    }
}

void Player::chooseGun()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && ammunition[0] > 0) {
        weapon.define("glock", x + width / 2, y + height / 2);
        activeGun = 0;
        sCnt = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && ammunition[1] > 0) {
        weapon.define("bondGun", x + width / 2, y + height / 2);
        activeGun = 1;
        sCnt = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && ammunition[2] > 0) {
        weapon.define("uzi", x + width / 2, y + height / 2);
        activeGun = 2;
        sCnt = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && ammunition[3] > 0) {
        weapon.define("ak47", x + width / 2, y + height / 2);
        activeGun = 3;
        sCnt = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && ammunition[4] > 0) {
        weapon.define("rifle", x + width / 2, y + height / 2);
        activeGun = 4;
        sCnt = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && ammunition[5] > 0) {
        weapon.define("smaw", x + width / 2, y + height / 2);
        activeGun = 5;
        sCnt = 0;
    }
}

void Player::award(int points) { score += points; }

void Player::ammunitionRestart()
{
    for (int i = 0; i < 6; i++) {
        if (i == 0)
            ammunition[i] = 40;
        if (i == 1)
            ammunition[i] = 25;
        if (i > 1)
            ammunition[i] = 0;
    }
    sCnt = 0;
    canFire = false;
}
