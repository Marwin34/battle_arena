#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.hpp"
#pragma once

#define BLOCK_SIZE      32
#define JUMP_SPEED      15
#define FALL_SPEED_MAX  15

class Player:public Entity{

    //FLAGI KLAWISZY
    bool Left,Right,Up;

public:
    int ammunition[6];
    int activeGun;

    Player();
    ~Player();

    void update(sf::Time,float,int);
    void chooseGun();
    void award(int);
    void ammunitionRestart();
};
