#pragma once
#include "SFML/Graphics.hpp"
#include "Textbox.h"
#include <vector>

enum class Direction { None, Up, Down, Left, Right };

struct SnakeSegment 
{   
    SnakeSegment(int x, int y) : position(x, y) {}
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake
{
    SnakeContainer m_snakeBody;
    int m_size; 
    Direction m_dir; 
    int m_speed; 
    int m_lives; 
    int m_score; 
    bool m_lost; 
    sf::RectangleShape bodyRect; 
    Textbox* textbox;

    void CheckCollision();

public:
    Snake(int blockSize, Textbox* text);
    ~Snake();

    void setDirection(Direction dir);
    Direction getDirection();
    float getSpeed();
    sf::Vector2i getPosition();
    int getLives();
    int getScore();
    void IncreaseScore();
    bool HasLost();

    void Lose();
    void ToggleLost();
    void GameOver(Textbox* text);
    Direction CheckingDirectionIsValid();

    void Extend();
    void Reset();

    void Move();
    void Tick();
    void Render(sf::RenderWindow& window);
    void Cut(int segments);
};