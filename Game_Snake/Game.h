#pragma once
#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

class Game {
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();

    Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();
   

private:
    Snake snake;
    Window window;
    World world;
    Textbox textbox, textGameOver;

    sf::Vector2f speed;
    float timer;
    sf::Clock clock;
    sf::RectangleShape rect;
};