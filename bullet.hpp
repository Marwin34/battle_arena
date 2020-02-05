#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define BLOCK_SIZE 32
#define PI 3.14159265
#define SPEED 5

class Bullet {
public:
    float x;
    float y;
    float spdX;
    float spdY;
    int width;
    int height;
    int ttl;
    bool toRemove;
    int dmg;

    std::string originName;

    sf::Sprite sprite;

    sf::Time lastUpdate;

    Bullet();
    ~Bullet();

    void draw(sf::RenderWindow*);
    void create(int, int, float, std::string, sf::Texture&, int, int);
    void update(sf::Time);
    bool colliding(int, int, int, int);
};
