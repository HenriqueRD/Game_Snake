#include "Textbox.h"

Textbox::Textbox() { Setup(5, 9, 200, sf::Vector2f(0.f, 0.f)); }

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos, int l_amount) 
{ 
	Setup(l_visible, l_charSize, l_width, l_screenPos); 
}

Textbox::~Textbox() { Clear(); }

void Textbox::Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos, int l_amount)
{
	m_amount = l_amount;
	m_numVisible = l_visible;
	sf::Vector2f l_offset(5.f, 5.f);

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(l_charSize);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(l_screenPos + l_offset);

	m_backdrop.setSize(sf::Vector2f(l_width, ( l_visible * (l_charSize * 1.9f))));
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_backdrop.setPosition(l_screenPos);
}

void Textbox::Add(std::string l_message)
{
	m_messages.push_back(l_message);

	if (m_messages.size() < m_amount) { return; }

	m_messages.erase(m_messages.begin());
}

void Textbox::Clear() { m_messages.clear(); }

void Textbox::Render(sf::RenderWindow& window)
{
	std::string l_content;

	for (auto& itr : m_messages) { l_content.append(itr + "\n"); }

	if (l_content != "") 
	{
		m_text.setString(l_content);
		window.draw(m_backdrop);
		window.draw(m_text);
	}
}