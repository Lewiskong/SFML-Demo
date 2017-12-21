#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    Game game;
    game.Run();
}