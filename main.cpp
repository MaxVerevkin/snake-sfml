#include "snake.hpp"

// Size of each block
#define BLOCK_SIZE 15 
// Windows size in terms of blocks
#define WIDTH 40
#define HEIGHT 30

// Speed of snake
// time (miliseconds) per block
#define TPB 120.f

int main() {
    // Main window
    sf::RenderWindow window(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE), "Snake");
    window.setVerticalSyncEnabled(true);

    // SFML Clock
    sf::Clock clock;

    // Game vars
    snakeGame game(WIDTH, HEIGHT, BLOCK_SIZE);
    snakeGameDir dir = snakeGameDir::Stay;
    snakeGameDir dirCur = snakeGameDir::Stay;

    // Loop
    while (window.isOpen()) {

        // Handle all events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Right && dirCur != snakeGameDir::Left)
                    dir = snakeGameDir::Right;
                if (event.key.code == sf::Keyboard::Left && dirCur != snakeGameDir::Right)
                    dir = snakeGameDir::Left;
                if (event.key.code == sf::Keyboard::Up && dirCur != snakeGameDir::Down)
                    dir = snakeGameDir::Up;
                if (event.key.code == sf::Keyboard::Down && dirCur != snakeGameDir::Up)
                    dir = snakeGameDir::Down;
                break;
            }   
        }

        // Get time
        int animationState = clock.getElapsedTime().asMilliseconds();
        if (animationState >= TPB) {
            clock.restart();
            dirCur = dir;
            game.move(dirCur);
        }

        // Game over
        if (game.gameOver) {
            window.close();
            break;
        }

        // Draw
        window.clear(sf::Color::Green);
        game.draw(&window, (float)clock.getElapsedTime().asMilliseconds()/TPB);
        window.display();
    }

    return 0;
}
