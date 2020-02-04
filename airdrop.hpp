#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.hpp"
#include "player.hpp"

#define BLOCK_SIZE      32
#define FALL_SPEED_MAX  15


class Airdrop:public Entity{
	enum class Type { MEDKIT, AMMO };

    Type kind;
public:
    bool toRemove;
    int amount;
    int index;

	Airdrop();
    Airdrop(int, int, int, sf::Texture&, sf::Texture&);
    ~Airdrop();
    bool colliding(int,int,Player&);
    void update(sf::Time);
    void draw(sf::RenderWindow*);

};
