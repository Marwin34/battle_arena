#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    srand(time(NULL));

    Game game;
    game.start();

    return 0;
}
