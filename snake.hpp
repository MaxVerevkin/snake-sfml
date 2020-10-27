#include <SFML/Graphics.hpp>

// Directions
enum class snakeGameDir { Right, Left, Up, Down, Stay };

// Linked list of 2D vectors
struct vectorList {
    sf::Vector2f vec;
    vectorList *next;
};

// Game controller
class snakeGame
{
private:
    int width, height;
    float blockSize;
    vectorList *snake;
    vectorList *head;
    sf::Vector2f foodPos;
    sf::Vector2f prevHeadPos;
    sf::Vector2f prevTailPos;
    sf::Shape *foodSprite;

    sf::Vector2f randPos();
    void genFood();

    sf::Vector2f mul(sf::Vector2f a, float b);
    sf::Vector2f moveForwardTo(sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float w);
public:
    bool gameOver;

    snakeGame(int width, int height, float blockSize);
    void move(snakeGameDir dir);
    void draw(sf::RenderWindow *window, float state);
};
