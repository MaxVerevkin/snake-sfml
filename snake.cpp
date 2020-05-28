#include "snake.hpp"

#include <stdlib.h>
#include <time.h>

snakeGame::snakeGame(int width, int height, float blockSize) {
    srand(time(NULL));

    // Init vars
    this->width = width;
    this->height = height;
    this->blockSize = blockSize;
    gameOver = false;

    // Init snake lest
    snake = new vectorList();
    snake->vec = randPos();
    snake->next =NULL;
    head = snake;
    prevHeadPos = snake->vec;
    prevTailPos = snake->vec;

    // Init food
    foodSprite = new sf::CircleShape(blockSize/2);
    foodSprite->setFillColor(sf::Color::Red);
    genFood();
}

void snakeGame::move(snakeGameDir dir) {
    prevHeadPos = head->vec;
    prevTailPos = snake->vec;
    
    sf::Vector2f newPos = head->vec;
    switch (dir)
    {
    case snakeGameDir::Right:
        newPos.x += 1;
        break;
    case snakeGameDir::Left:
        newPos.x -= 1;
        break;
    case snakeGameDir::Up:
        newPos.y -= 1;
        break;
    case snakeGameDir::Down:
        newPos.y += 1;
        break;
    }

    // Check walls
    if (newPos.x < 0 || newPos.y < 0 || newPos.x >= width || newPos.y >= height)
        gameOver = true;

    // Eat food
    if (newPos.x == foodPos.x && newPos.y == foodPos.y) {
        head->next = new vectorList();
        head = head->next;
        head->next = NULL;
        head->vec = newPos;
        genFood();
    }
    // Just move and check overlaps
    else {
        vectorList *temp = snake;
        while (temp->next) {
            if (temp->vec == head->vec)
                gameOver = true;
            temp->vec = temp->next->vec;
            temp = temp->next;
        }
        head->vec = newPos;
    }
}

void snakeGame::draw(sf::RenderWindow *window, float state) {
    // Normolize state
    if (state > 1)
        state = 1;

    // Block snape
    sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
    block.setFillColor(sf::Color::Blue);

    // Animated head
    block.setPosition(mul(lerp(prevHeadPos, head->vec, state), blockSize));
    window->draw(block);

    // Animated tail
    block.setPosition(mul(lerp(prevTailPos, snake->vec, state), blockSize));
    window->draw(block);

    vectorList *temp = snake;
    while (temp->next) {
        block.setPosition(mul(temp->vec, blockSize));
        window->draw(block);
        temp = temp->next;
    }

    // Food
    window->draw(*foodSprite);
}

sf::Vector2f snakeGame::randPos() {
    return sf::Vector2f(rand() % width, rand() % height);
}

void snakeGame::genFood() {
    foodPos = randPos();
    foodSprite->setPosition(foodPos.x * blockSize, foodPos.y * blockSize);
}

float snakeGame::manhattan(sf::Vector2f a, sf::Vector2f b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

sf::Vector2f snakeGame::moveForwardTo(sf::Vector2f a, sf::Vector2f b) {
    if (a.x < b.x)
        a.x += 1;
    else if (a.x > b.x)
        a.x -= 1;
    else if (a.y < b.y)
        a.y += 1;
    else if (a.y > b.y)
        a.y -= 1;
    return a;
}

sf::Vector2f snakeGame::mul(sf::Vector2f a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

sf::Vector2f snakeGame::lerp(sf::Vector2f a, sf::Vector2f b, float w) {
    a.x += (b.x - a.x) * w;
    a.y += (b.y - a.y) * w;
    return a;
}
