#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Window 
{
	sf::RenderWindow window;
	sf::Vector2u v_windowSize;
	std::string s_windowTitle;
	bool b_isDone;
	bool b_isFullscreen;

	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();
	void Destroy();

public:
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();
	
	void ClearDraw();
	void ShowDraw();

	void Update();

	bool isClose();
	bool isFullscreen();
	sf::Vector2u getWindowSize();
	sf::RenderWindow* GetRenderWindow();
	void ToggleFullscreen();

	void Draw(sf::Drawable& drawable);
};