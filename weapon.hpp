#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define BLOCK_SIZE 32

enum class WeaponSound { GUN, BONDGUN, UZI, AK, RIFFLE, SMAW, NONE };

class Weapon {
    int x;
    int y;
    int difX1;
    int difX2;
    int difY;
    int oX;
    int oY;
    int gX;
    int attackSpeed;

    std::string name;

    int frame;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    int dmg;
    WeaponSound sound_type;

    Weapon();
    ~Weapon();

    void update(int, int, float);
    void define(std::string, int, int);
    void draw(sf::RenderWindow*);
    int getFrame();
    int getAttackSpeed();
    int getX();
    int getY();
};
