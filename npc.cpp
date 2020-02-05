#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <Math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "npc.hpp"

NPC::NPC()
{
    x = 0;
    y = 0;

    hp = 0;
    maxHp = hp;

    width = 0;
    height = 0;

    // SHOOT COOLDOWN
    sCnt = 0;

    name = "NONAME";

    lastUpdate = sf::Time::Zero;

    cUp = false;
    cRight = false;
    cDown = false;
    cLeft = false;
    cNext = false;
    repair = false;
    lStop = false;
    rStop = false;

    canFire = false;

    toRemove = false;

    isAiming = false;

    dir = none;
    lastDir = dir;

    // FRAME INDICATORS INITIALIZATION
    frameX = 4;
    frameY = 0;

    score = 0;

    canSeePlayer = true;
}

NPC::~NPC() { }

void NPC::create(int xx, int yy, std::string varName)
{

    if (varName == "Nic") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/ciemnoziel.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 35;
        maxHp = hp;

        weapon.define("nicWmk1", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 15;
    }
    if (varName == "Nic2") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/szary.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 50;
        maxHp = hp;

        weapon.define("nicWmk2", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 25;
    }
    if (varName == "Nic3") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/nic.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 50;
        maxHp = hp;

        weapon.define("nicWmk7", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 35;
    }
    if (varName == "Nic4") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/szary2.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 100;
        maxHp = hp;

        weapon.define("nicWmk3", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 50;
    }
    if (varName == "Nic5") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/_szary2.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 110;
        maxHp = hp;

        weapon.define("nicWmk4", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 75;
    }
    if (varName == "Nic6") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/_szary.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 115;
        maxHp = hp;

        weapon.define("nicWmk5", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 100;
    }
    if (varName == "Nic7BOSS") {
        name = varName;
        x = xx;
        y = yy;

        image.loadFromFile("resources/img/_czerwony.png");

        width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
        height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

        texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        hp = 350;
        maxHp = hp;

        weapon.define("nicWmk6", x, y);

        hpBarTexture.loadFromFile("resources/img/hp.png");
        hpBar.setTexture(hpBarTexture);

        score = 1000;
    }
}

void NPC::Ai(int playerX, int playerY, int playerWidth, int playerHeight)
{

    if (dir == none && lStop && rStop) {
        srand(time(NULL));
        if ((std::rand() % 2) + 0 == 0)
            dir = left;
        else
            dir = right;
    }
    if (dir == left && (!lStop || cLeft))
        dir = right;
    if (dir == right && (!rStop || cRight))
        dir = left;
    if (!lStop && !rStop)
        dir = none;

    if (fabs((x + width / 2) - (playerX + playerWidth / 2)) < 256
        && fabs((y + height / 2) - (playerY + playerHeight / 2)) < 256 && canSeePlayer) {
        isAiming = true;
        if (x == (x / BLOCK_SIZE) * BLOCK_SIZE) {
            dir = none;
            if (sCnt > weapon.getAttackSpeed()) {
                canFire = true;
            }
            if ((x + width / 2) - (playerX + playerWidth / 2) < 0)
                frameY = 1;
            else
                frameY = 0;
            frameX = 4;
        }
    } else
        isAiming = false;
}

void NPC::update(
    sf::Time timer, int playerX, int playerY, int playerWidth, int playerHeight, float angle)
{
    if (repair) {
        y = (y / height) * height;
        repair = false;
    }

    if (timer.asMilliseconds() - lastUpdate.asMilliseconds() > 20) {
        Ai(playerX, playerY, playerWidth, playerHeight);

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
        if (movePhase == fall) {
            if (fallSpeed < FALL_SPEED_MAX)
                fallSpeed += g;
            if (cNext)
                fallSpeed = (y / height + 1) * height - y;
            y += fallSpeed;
        }

        if (sCnt > 10) {
            if (dir == left)
                x -= 4;
            if (dir == right)
                x += 4;

            if (dir == left)
                frameY = 0;
            if (dir == right)
                frameY = 1;

            if (dir == lastDir && dir != none)
                frameX++;
            if (frameX > 15)
                frameX = 0;
            texture.loadFromImage(
                image, sf::IntRect(frameX / 4 * width, frameY * height, width, height));
        }

        cUp = false;
        cRight = false;
        cDown = false;
        cLeft = false;
        cNext = false;
        lStop = false;
        rStop = false;

        sCnt++;

        if (isAiming) {
            weapon.update(x + width / 2, y + height / 2, angle);
        } else {
            if (frameY == 1)
                angle = 90;
            if (frameY == 0)
                angle = -90;
            weapon.update(x + width / 2, y + height / 2, angle);
        }

        hpBar.setPosition(x - 4, y - 5);
        hpBar.setScale(static_cast<float>(hp) / static_cast<float>(maxHp) > 0
                ? static_cast<float>(hp) / static_cast<float>(maxHp)
                : 0,
            1);

        lastDir = dir;
        lastUpdate = timer;

        sprite.setPosition(x, y);
    }
    canSeePlayer = true;
}
