#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "apple.h"

class Snake
{
    private:
        unsigned int    width;
        unsigned int    height;
        float           snake_velocity;
        sf::CircleShape Player;
        sf::Vector2f    direction;
        sf::Vector2f    initial_pos;

        bool Clicked = false;


    public:

    Snake(float radius, float set_speed, sf::Vector2f initial_position, float fps) {
            Player.setRadius(radius);
            Player.setPosition({initial_position});
            initial_pos = initial_position;
            float delta_time = 1.f / fps;
            snake_velocity = set_speed * delta_time;
    };

    void draw(sf::RenderWindow& window) {
        window.draw(Player);
    }

    bool Is_SnakeLost(sf::Vector2f playerPosition, float diameter, int width, int height) {
        if (playerPosition.x < 0) {
            Player.setPosition({initial_pos});
            return true;
        } else if (playerPosition.x > width - diameter){
            Player.setPosition({initial_pos});
            return true;
        } else if (playerPosition.y < 0){
            Player.setPosition({initial_pos});
            return true;
        } else if (playerPosition.y > height - diameter){
            Player.setPosition({initial_pos});
            return true;
        }
        return false;
    }
        // It's using the method Is_SnakeLost
    bool detectColision_Borders(unsigned int width, unsigned int height) {
        sf::Vector2f position = Player.getPosition();
        float diameter        = 2.f * Player.getRadius();

        return Is_SnakeLost(position, diameter, width, height);
    }

    bool checkingAppleColision(const Apple& apple){
        return apple.colisionApple(Player);
    }

    sf::Vector2f getAxis(sf::Vector2f vector) {

        if (!Clicked) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && direction.x != 1.f) {
                Clicked = true;
                vector  = {-1.f, 0.f};
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) && direction.x != -1.f) {
                Clicked = true;
                vector  = {1.f, 0.f};
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) && direction.y != -1.f){
                Clicked = true;
                vector  = {0.f, 1.f};
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && direction.y != 1.f) {
                Clicked = true;
                vector  = {0.f, -1.f};
            }
        }
        return vector;

    }
    void KeyClicked() {
        Clicked = false;
    }

    void movingSnake() {

        KeyClicked();
        direction = getAxis(direction);
        // it normalizes the direction when two buttons are pressed
        if  (direction.x != 0 || direction.y != 0){
            Player.setFillColor(sf::Color(100, 226, 180)); // Active
        } else {
            Player.setFillColor(sf::Color(23, 115, 82)); // S   tand by
        }
        Player.move({direction * snake_velocity});
    }
};

#endif // SNAKE_H
