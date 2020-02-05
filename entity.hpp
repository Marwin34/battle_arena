#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "weapon.hpp"

#pragma once

#define BLOCK_SIZE 32

class Entity {
protected:
    std::string name;

    sf::Sprite sprite;
    sf::Image image;
    sf::Texture texture;
    sf::Time lastUpdate;

    sf::Sprite hpBar;
    sf::Texture hpBarTexture;

    // GRAVITY
    int g;

    // JUMP PHASE
    float jumpSpeed;
    float fallSpeed;

    enum side {
        stand,
        fly,
        fall,
    };

    int movePhase;

    // FRAME INDICATORS
    int frameY;
    int frameX;

    // LAST DIRECTION ENUM
    enum direction {
        inAir,
        left,
        right,
        none,
    };

    // COLLISION FLAGS
    bool cUp, cRight, cDown, cLeft, cNext, repair, rStop, lStop,
        scUp; // rStop, lStop USED IN NPC

    int dir;
    int lastDir;

    int maxHp;

    int score;

    bool canSeePlayer;

public:
    Weapon weapon;

    int x;
    int y;

    int width;
    int height;

    int hp;

    int sCnt;
    bool canFire;

    Entity();
    ~Entity();

    void LineCast(sf::Vector2f, sf::Vector2f, int, int);
    void draw(sf::RenderWindow*);
    void resetScore();
    void collisionDetect(int, int, int, int);
    std::string getName();
    int getHp();
    int getMaxHp();
    int getScore();
    sf::Vector2f vectorDir(sf::Vector2f, sf::Vector2f);
    sf::Vector2f transformPos();
    bool compareVectorsDir(sf::Vector2f, sf::Vector2f);
};
