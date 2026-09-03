#ifndef EVENTS_H
#define EVENTS_H
#include "apple.h"
#include "snake.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Do not delete this file.

class Events{
    private:

    int snake_score = 0;
    int& score = snake_score;

    Snake snake;
    Apple apple;

    sf::Font font;

    public:

    void Showing_Messages(sf::RenderWindow& window, std::string pathfont, std::string Message) {
        if (!font.openFromFile(pathfont))
        {
            std::cout << "Error.\n";
        }

        sf::Text ScoreText(font);

        ScoreText.setString(Message);
        ScoreText.setCharacterSize(64);

        window.draw(ScoreText);
    } // work in Progress. It does not work properly.

    void Snake_Lost(sf::RenderWindow& windowMain, int width, int height) {

        if (!snake.detectColision_Borders(width, height)) {
            snake.movingSnake();
        } else {
            score = 0;
            Showing_Messages(windowMain, "./build/Google_Sans/GoogleSans.ttf", "You lost.");
        }
    }


};

#endif // EVENTS_H
