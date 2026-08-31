#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>

class Snake
{
    private:
        unsigned int    width;
        unsigned int    height;
        bool            state;
        sf::CircleShape Player;
        sf::Vector2f    direction;
        float           snake_velocity;
        sf::Vector2f    initial_pos;

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
    bool detectColision(unsigned int width, unsigned int height) {
        sf::Vector2f position = Player.getPosition();
        float diameter = 2.f * Player.getRadius();

        return Is_SnakeLost(position, diameter, width, height);
    }
    float getAxis(sf::Keyboard::Scan negativeKey, sf::Keyboard::Scan positiveKey, float vector) {

        if (sf::Keyboard::isKeyPressed(negativeKey)) {
            vector -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(positiveKey)) {
            vector += 1.f;
        }
        return vector;
    }

    void movingSnake(bool player_state) {
        direction = {0.f, 0.f};

        direction.x = getAxis(sf::Keyboard::Scan::A, sf::Keyboard::Scan::D, direction.x);
        direction.y = getAxis(sf::Keyboard::Scan::W, sf::Keyboard::Scan::S, direction.y);
        // it normalizes the direction when two buttons are pressed
        if  (direction.x != 0 || direction.y != 0){
            direction = direction.normalized();
            Player.setFillColor(sf::Color(100, 226, 180));
        } else {
            Player.setFillColor(sf::Color(23, 115, 82));
        }
        Player.move({direction * snake_velocity});
    }
};

#endif // SNAKE_H
