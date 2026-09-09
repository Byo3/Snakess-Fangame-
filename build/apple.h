#ifndef APPLE_H
#define APPLE_H
#include <SFML/Graphics.hpp>
#include <random>

class Apple{
    private:
        sf::CircleShape apple;
        float     diameter;
        sf::Vector2f initial_pos;
    public:

        Apple(float radius, sf::Vector2f initial_position){
            diameter = 2 * radius;
            apple.setRadius(radius);
            apple.setFillColor(sf::Color(217, 35, 68));
            initial_pos = initial_position;
            apple.setPosition({initial_position});
        }

        void draw(sf::RenderWindow& window) {
            window.draw(apple);
        }

        int generatingPositions(int Limit){
            // Obtains a seed from hardware
            std::random_device rd;
            std::mt19937 gen(rd());
            // Set a range
            std::uniform_int_distribution<int> Axis(0, Limit);
            return Axis(gen);
        }
        void spawn_Apples(int window_width, int window_height) {
            float Axis_x = generatingPositions(window_width);
            float Axis_y = generatingPositions(window_height);

            apple.setPosition({Axis_x, Axis_y});
        }

        bool colisionApple(const sf::CircleShape& player) const {
            auto boundsPlayer = player.getGlobalBounds();
            auto boundsApple  = apple.getGlobalBounds();

            if (boundsPlayer.findIntersection(boundsApple)){
                return true;
            }
            return false;
        }

        int incrementScore(int& initial_score) {
            return initial_score += 1;
        }

        void SpawnReset() {
            apple.setPosition(initial_pos);
        }
};

#endif // APPLE_H
