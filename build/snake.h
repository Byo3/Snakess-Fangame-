#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include <deque>
#include "apple.h"

class Snake {
    private:
        sf::CircleShape SnakePlayer;
        sf::CircleShape Body_Segmetations;
        sf::Vector2f    Snakedirection;
        sf::Vector2f    initial_pos;
        std::deque<sf::Vector2f> Snake_Bodys;
        bool Clicked = false;

    public:
        unsigned int width;
        unsigned int height;
        float        snake_velocity;

        int         growthPending = 0;

        Snake(float radius, float set_speed, sf::Vector2f initial_position, float fps) {
                SnakePlayer.setRadius(radius);
                SnakePlayer.setPosition({initial_position});

                Body_Segmetations.setRadius(radius);
                Body_Segmetations.setFillColor(sf::Color(45, 173, 81));

                initial_pos = initial_position;
                float delta_time = 1.f / fps;
                snake_velocity = set_speed * delta_time;
                Reset();
        };
        void Reset(){
            Snakedirection = {0.f, 0.f};
            growthPending = 0;
            Snake_Bodys.clear();
        }
        void Getting_PreviousPositions(const Apple& apple) {
            Snake_Bodys.push_back(SnakePlayer.getPosition());

            if (growthPending > 0) {
                growthPending--;

            } else{
                Snake_Bodys.pop_front();
            }
        }
        void drawSnake(sf::RenderWindow& window) {
            window.draw(SnakePlayer);
        }

        void drawBody(sf::RenderWindow& window) {
            for (const auto& Previous_Position : Snake_Bodys) {
                Body_Segmetations.setPosition(Previous_Position);
                window.draw(Body_Segmetations);
            }
        }

        bool Is_SnakeLost(sf::Vector2f playerPosition, float diameter, int width, int height) {
            auto boundsHead = SnakePlayer.getGlobalBounds();
            auto boundsBody  = Body_Segmetations.getLocalBounds();

            if (playerPosition.x < 0) {
                SnakePlayer.setPosition({initial_pos});
                return 1;
            } else if (playerPosition.x > width - diameter){
                SnakePlayer.setPosition({initial_pos});
                return 1;
            } else if (playerPosition.y < 0){
                SnakePlayer.setPosition({initial_pos});
                return 1;
            } else if (playerPosition.y > height - diameter){
                SnakePlayer.setPosition({initial_pos});
                return 1;
            } else if (boundsHead.findIntersection(boundsBody)) {
                SnakePlayer.setPosition({initial_pos});
                return 1;
            }
            return 0;
        }
            // It's using the method Is_SnakeLost
        bool detectColision_Borders(unsigned int width, unsigned int height) {
            sf::Vector2f Old_position = SnakePlayer.getPosition();
            float diameter        = 2.f * SnakePlayer.getRadius();

            return Is_SnakeLost(Old_position, diameter, width, height);
        }

        bool checkingAppleColision(const Apple& apple){
            return apple.colisionApple(SnakePlayer);
        }

        sf::Vector2f getAxis(sf::Vector2f vector) {
            if (!Clicked) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && Snakedirection.x != 1.f) {
                    Clicked = true;
                    vector  = {-1.f, 0.f};
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) && Snakedirection.x != -1.f) {
                    Clicked = true;
                    vector  = {1.f, 0.f};
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) && Snakedirection.y != -1.f){
                    Clicked = true;
                    vector  = {0.f, 1.f};
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && Snakedirection.y != 1.f) {
                    Clicked = true;
                    vector  = {0.f, -1.f};
                }
            }
            return vector;
        }

        void ResetClicked() {
            Clicked = false;
        }

        void movingSnake() {
            ResetClicked();
            Snakedirection = getAxis(Snakedirection);

            // it normalizes the direction when two buttons are pressed
            if  (Snakedirection.x != 0 || Snakedirection.y != 0){
                SnakePlayer.setFillColor(sf::Color(100, 226, 180)); // Active
            } else {
                SnakePlayer.setFillColor(sf::Color(23, 115, 82)); // Stand by
            }
            SnakePlayer.move({Snakedirection * snake_velocity});
        }
}; // Snake class

#endif // SNAKE_H
