#include "snake.h"
#include <SFML/Graphics.hpp>
// #include <random>
// #include <vector>
// #include <cmath>

int main()
{
    unsigned int width  = 600;
    unsigned int height = 600;
    sf::RenderWindow window(sf::VideoMode({width, height}), "SnakeGame");

    // Radius, speed, initial position, fps
    Snake snake(25.f, 100.f, {100,400}, 24.f);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

        }
        window.clear();

        snake.draw(window);
        snake.movingSnake(snake.detectColision(width, height));

        window.display();
    }
}
