#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using MessageContainer = std::vector<std::string>;

class Textbox {
	MessageContainer m_messages;
	int m_numVisible;
	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_text;
	int m_amount;

public:
	Textbox();
	Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos, int l_amount = 6);
	~Textbox();

	void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos, int l_amount = 6);
	void Add(std::string l_message);
	void Clear();
	void Render(sf::RenderWindow& window);
};