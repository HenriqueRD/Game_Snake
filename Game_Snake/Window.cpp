#include "Window.h"

void Window::Setup(const std::string& title, const sf::Vector2u& size)
{
	s_windowTitle = title;
	v_windowSize = size;
	b_isDone = false;
	b_isFullscreen = false;
	Create();
}

void Window::Create()
{
	bool style = (b_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

	window.create({v_windowSize.x, v_windowSize.y, 32}, s_windowTitle, style);
	//window.setFramerateLimit(10);
}

void Window::Update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) { b_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { ToggleFullscreen(); }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { b_isDone = true; }
	}
}

void Window::ToggleFullscreen()
{
	b_isFullscreen = !b_isFullscreen;
	Destroy();
	Create();
}

void Window::Destroy() { window.close(); }

Window::Window(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }

Window::~Window() { Destroy(); }

void Window::ClearDraw() { window.clear(); }

void Window::ShowDraw() { window.display(); }

bool Window::isClose() { return b_isDone; }

bool Window::isFullscreen() { return b_isFullscreen; }

sf::Vector2u Window::getWindowSize() { return v_windowSize; }

sf::RenderWindow* Window::GetRenderWindow()
{
	return &window;
}

void Window::Draw(sf::Drawable& drawable) { window.draw(drawable); }
