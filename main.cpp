#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game.hpp"


int main()
{
	srand(time(NULL));

    Game game;
    game.start();

    return 0;
}
