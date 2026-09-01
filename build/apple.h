#ifndef APPLE_H
#define APPLE_H
#include <SFML/Graphics.hpp>
#include <random>

struct Apple{
    int snake_Score = 0;

    sf::CircleShape apple;

    Apple(float radius, sf::Vector2f initial_position){
        apple.setRadius(radius);
        apple.setPosition({initial_position});
    }

    void draw(sf::RenderWindow& window) {window.draw(apple);}

    int generatingPositions(int Limit){
        // Obtains a seed from hardware
        std::random_device rd;
        std::mt19937 gen(rd());
        // Set a range
        std::uniform_int_distribution<int> Axis(0, Limit);
        return Axis(gen);
    }

    void spawning_Apples(int window_width, int window_height) {
        if (snake_Score != 0){
            float Axis_x = generatingPositions(window_width);
            float Axis_y = generatingPositions(window_height);

            apple.setPosition({Axis_x, Axis_y});
        }
    }
};

#endif // APPLE_H
