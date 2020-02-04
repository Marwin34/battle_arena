#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

    //HP BAR
    sf::Sprite hpBar;
    sf::Texture hpBarTexture;

    //GRAWITACJA
    int g;

    //FAZA SKOKU
    float jumpSpeed;
    float fallSpeed;

    enum side{
        stand,
        fly,
        fall,
    };

    int movePhase;

    //KLATKI
    int frameY;
    int frameX;

    //ZAPAMIETYWANIE OSTATNIEGO KIERUNKU
    enum direction {
        inAir,
        left,
        right,
        none,
    };

    //FLAGI KOLIZYJNE
    bool cUp,cRight,cDown,cLeft,cNext,repair,rStop,lStop,scUp;//rStop, lStop WYKORZYSTYWANE W RUCHU NPC

    //KIERUNKI
    int dir;
    int lastDir;

    //MAX HP
    int maxHp;

    int score;

    bool canSeePlayer;

public:
    //BROŃ
    Weapon weapon;

    int x;
    int y;

    int width;
    int height;

    int hp;

    //COUNTER STRZAŁU
    int sCnt;
    //FLAGA STRZA£U
    bool canFire;

    Entity();
    ~Entity();

    void LineCast(sf::Vector2f, sf::Vector2f, int, int);
    void draw(sf::RenderWindow*);
    void resetScore();
    void collisionDetect(int,int,int,int);
    std::string getName();
    int getHp();
    int getMaxHp();
    int getScore();
    sf::Vector2f vectorDir(sf::Vector2f, sf::Vector2f);
    sf::Vector2f transformPos();
    bool compareVectorsDir(sf::Vector2f, sf::Vector2f);
};
