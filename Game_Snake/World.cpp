#include "World.h"

World::World(sf::Vector2u windSize)
{
	m_blockSize = 16;
	m_windowSize = windSize;

	RespawnApple();

	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);

	//Defindo as posições das 4 paredes
	for (int i = 0; i < 4; ++i) 
	{
		m_bounds[i].setFillColor(sf::Color(194, 68, 0, 255));

		//Se for impar define o tamanho na cordenada X
		if ((i + 1) % 2) { m_bounds[i].setSize(sf::Vector2f(windSize.x, m_blockSize)); }

		//Se for par define o tamanho na cordenada Y
		else { m_bounds[i].setSize(sf::Vector2f(m_blockSize, windSize.y)); }

		//Pega a 2 primeiras paredes e define elas na posição no canto superior esquerdo
		if (i < 2) { m_bounds[i].setPosition(0, 0); }

		//Pega as 2 ultimas e define elas na posição no canto inferior direito
		else 
		{
			//Desloca o ponto de origem
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	} 
}

World::~World() { }

int World::GetBlockSize() { return m_blockSize; }

void World::RespawnApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;

	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

void World::Update(Snake& snake)
{
	//Checando se a posição da Cobra é a mesma que a da Maçã
	if (snake.getPosition() == m_item) 
	{
		snake.Extend();
		snake.IncreaseScore();
		RespawnApple();
	} 

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	//Checando se a posição da Cobra é a mesma que a do Limite
	if (snake.getPosition().x <= 0 ||
		snake.getPosition().y <= 0 ||
		snake.getPosition().x >= gridSize_x - 1 ||
		snake.getPosition().y >= gridSize_y - 1)
	{
		snake.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window)
{
	//Rendeniza as 4 paredes
	for (int i = 0; i < 4; ++i) {
		l_window.draw(m_bounds[i]);
	}

	//Rendeniza a Maçã
	l_window.draw(m_appleShape);
}