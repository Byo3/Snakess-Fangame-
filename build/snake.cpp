#include "snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const unsigned int width  = 600;
    const unsigned int height = 600;

    sf::Vector2f initial_PositionlApple = {400, 400};

    sf::Vector2f initial_PositionSnake  = {100,400};

    sf::RenderWindow window(sf::VideoMode({width, height}), "SnakeGame");

    sf::Font font;
    if (!font.openFromFile("./build/Google_Sans/GoogleSans.ttf")) {
        std::cout << "Error.\n";
    }
    // Drawing the Score Text
    int snake_score = 0;
    int& score = snake_score;

    sf::Text ScoreText(font);
    ScoreText.setString(std::to_string(score));
    ScoreText.setCharacterSize(64);

    // Drawing Messages.
    bool ShowMessage = false;

    sf::Text Messages(font);
    Messages.setCharacterSize(64);
    Messages.setPosition({150, 300});
    Messages.setString("You lost.");

    // Radius, speed, initial position, fps
    Snake snake(15.f, 80.f, initial_PositionSnake, 24.f);
    // Radius, initial position.
    Apple apple(15.f, initial_PositionlApple);

    window.setFramerateLimit(60);

    sf::Clock clock;
    sf::Time Duration = sf::seconds(0.5f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Time elapsedTime = clock.getElapsedTime();

        if (!snake.detectColision_Borders(width, height)) {
            snake.movingSnake();

            snake.Getting_PreviousPositions(apple);

            // Note: Inserts these conditionals below into separated functions.
            if (snake.checkingAppleColision(apple)) {
                snake.growthPending += 8;
                apple.spawn_Apples(width, height);
                std::cout << apple.incrementScore(score) << "\n";
                ScoreText.setString(std::to_string(score));
            }


        } else {
            ShowMessage = true;
            clock.restart();
            elapsedTime = sf::Time::Zero;

            // Score Resets
            score = 0;
            ScoreText.setString(std::to_string(score));

            // Spawn resets
            apple.SpawnReset();
            snake.Reset();
        }
        window.clear();

        apple.draw(window);

        snake.drawBody(window);
        snake.drawSnake(window);

        // drawing puntuation
        window.draw(ScoreText);

        if (ShowMessage) {
            if (elapsedTime < Duration) {
                window.draw(Messages);
            } else {
                ShowMessage = false;
            }
        }


        window.display();
    }
}
