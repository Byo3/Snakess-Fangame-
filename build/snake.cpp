#include "snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    unsigned int width  = 600;
    unsigned int height = 600;

    int snake_score = 0;
    int& score = snake_score;

    sf::RenderWindow window(sf::VideoMode({width, height}), "SnakeGame");

    // Radius, speed, initial position, fps
    Snake snake(25.f, 100.f, {100,400}, 24.f);

    // Radius, initial position.
    Apple apple(25.f, {400, 400});

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

        }
        window.clear();

        apple.draw(window);

        if (snake.checkingAppleColision(apple))
            apple.spawn_Apples(width, height);
            score++;
            std::cout << score << "\n";

        snake.draw(window);
        snake.movingSnake(snake.detectColision_Borders(width, height));

        window.display();
    }
}
