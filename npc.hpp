#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.hpp"

#define BLOCK_SIZE      32
#define JUMP_SPEED      15
#define FALL_SPEED_MAX  15


class NPC:public Entity {

public:
    bool toRemove,isAiming;

    NPC();
    ~NPC();

    void create(int,int,std::string);
    void Ai(int,int,int,int);
    void update(sf::Time,int,int,int,int,float);
};
