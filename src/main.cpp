#include <iostream>
#include "european_conquest/graphics/ui/GameWindow.h"

int main()
{
    european_conquest::GameWindow window(
        sf::VideoMode({ 1920, 1080 }),
        "European Conquest"
    );

    window.run();

    return 0;
}