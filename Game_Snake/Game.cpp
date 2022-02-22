#include "Game.h"

Game::Game() : 
	window("Snake Game", sf::Vector2u(32 * 16, 32 * 16)), 
	world(sf::Vector2u(32 * 16, 32 * 16)),
	snake(16, &textbox),
	textbox(),
	textGameOver()
{
	textGameOver.Setup(3, 30, 20 * 16, sf::Vector2f(window.getWindowSize().x / 2 - 10*16, window.getWindowSize().y / 2 - 10 * 16),4);
	textbox.Setup(3, 15, 8*16, sf::Vector2f(0, 0));

	clock.restart();
	srand(time(nullptr));

	textbox.Add("O jogo Snake.");

	timer = 0.0f;
}

Game::~Game()
{
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& snake.CheckingDirectionIsValid() != Direction::Down)
	{
		snake.setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& snake.CheckingDirectionIsValid() != Direction::Up)
	{
		snake.setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& snake.CheckingDirectionIsValid() != Direction::Right)
	{
		snake.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& snake.CheckingDirectionIsValid() != Direction::Left)
	{
		snake.setDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && snake.HasLost())
	{
		snake.Reset();
		textGameOver.Clear();
	}
}

void Game::Update()
{	
	window.Update();
	float timestep = 1.0f / snake.getSpeed();
	if (!snake.HasLost())
	{
		if (timer >= timestep)
		{
			snake.Tick();
			world.Update(snake);
			timer -= timestep;
		}
	}
	else
	{
		snake.GameOver(&textGameOver);
	}
}

void Game::Render()
{
	window.ClearDraw();
	snake.Render(*window.GetRenderWindow());
	world.Render(*window.GetRenderWindow());
	textbox.Render(*window.GetRenderWindow());
	textGameOver.Render(*window.GetRenderWindow());
	window.ShowDraw();
}

Window* Game::GetWindow()
{
	return &window;
}

sf::Time Game::GetElapsed() { return clock.getElapsedTime(); }

void Game::RestartClock() { timer += clock.restart().asSeconds(); }