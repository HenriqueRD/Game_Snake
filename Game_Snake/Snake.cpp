#include "Snake.h"
#include <iostream>

void Snake::CheckCollision()
{
    if (m_snakeBody.size() < 5) { return; }
    //Verifica se a cabeça colidou com o corpo
    SnakeSegment& head = m_snakeBody.front();
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
    {
        if (itr->position == head.position) 
        {
            int segments = m_snakeBody.end() - itr;
            Cut(segments);
            break;
        }
    }
}

Snake::Snake(int blockSize, Textbox* text)
{
    m_size = blockSize;
    textbox = text;
    bodyRect.setSize(sf::Vector2f(float(m_size) - 1.f, float(m_size) - 1.f));
    Reset();
}

Snake::~Snake() { }

void Snake::Extend()
{
    if (m_snakeBody.empty()) { return; }

    SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];

    if (m_snakeBody.size() > 1)
    {
        //Acresenta mais um bloco na cobra
        //Verifica se meu Y e` - ou + para colocar um novo segmento
        SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 1];
        if (tail_head.position.x == tail_bone.position.x) {
            if (tail_head.position.y > tail_bone.position.y) {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y + 1));
            }
            else {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y - 1));
            }
        }

        //Verifica se meu X e` - ou + para colocar um novo segmento
        else if (tail_head.position.y == tail_bone.position.y) {
            if (tail_head.position.x > tail_bone.position.x) {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x + 1, tail_head.position.y));
            }
            else {
                m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x - 1, tail_head.position.y));
            }
        }
    }
    else {
        if (m_dir == Direction::Up) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x, tail_head.position.y + 1));
        }
        else if (m_dir == Direction::Down) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x, tail_head.position.y - 1));
        }
        else if (m_dir == Direction::Left) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x + 1, tail_head.position.y));
        }
        else if (m_dir == Direction::Right) {
            m_snakeBody.push_back(SnakeSegment(
                tail_head.position.x - 1, tail_head.position.y));
        }
    }
}

void Snake::Reset() {
    m_snakeBody.clear();

    m_snakeBody.push_back(SnakeSegment(9, 8));
    m_snakeBody.push_back(SnakeSegment(10, 8));
    m_snakeBody.push_back(SnakeSegment(11, 8));
    m_snakeBody.push_back(SnakeSegment(12, 8));

    setDirection(Direction::None);
    m_speed = 10;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
}

void Snake::Move()
{
    //Move a cobra para posição do meu arry da frente
    for (int i = m_snakeBody.size() - 1; i > 0; i--)
    {
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }

    if (m_dir == Direction::Left) { --m_snakeBody[0].position.x; }

    else if (m_dir == Direction::Right ) { ++m_snakeBody[0].position.x; }

    else if (m_dir == Direction::Up) { --m_snakeBody[0].position.y; }

    else if (m_dir == Direction::Down) { ++m_snakeBody[0].position.y; }
}

void Snake::Tick()
{
    if (m_snakeBody.empty()) { return; }
    if (m_dir == Direction::None) { return; }
    Move();
    CheckCollision();
}

void Snake::Render(sf::RenderWindow& window)
{
    if (m_snakeBody.empty()) { return; }
    auto head = m_snakeBody.begin();

    //Rendenizando a cabeça 
    bodyRect.setFillColor(sf::Color::Yellow);
    bodyRect.setPosition(head->position.x * float(m_size), head->position.y * float(m_size));
    window.draw(bodyRect);

    //Rendenizando o esqueleto
    bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) 
    {
        bodyRect.setPosition(itr->position.x * float(m_size), itr->position.y * float(m_size));
        window.draw(bodyRect);
    }
}

void Snake::Cut(int segments)
{
    //Ira tirar os segmentos do vector da cobra, na posição que ela colidiu com ela mesma
    for(int i = 0; i < segments; ++i) { m_snakeBody.pop_back(); }

    --m_lives;
    textbox->Add(" Life: " + std::to_string((long long)getLives()) + " / 3");

    if (!m_lives) { 
        Lose(); 
        return; }
}

void Snake::setDirection(Direction dir) { m_dir = dir; }

Direction Snake::getDirection() { return m_dir; }

float Snake::getSpeed() { return m_speed; }

sf::Vector2i Snake::getPosition()
{
    return (!m_snakeBody.empty() ?
        m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives() { return m_lives; }

int Snake::getScore() { return m_score; }

void Snake::IncreaseScore() 
{ 
    m_score += 10;
    textbox->Add(" Score: " + std::to_string((long long)getScore()));
}

bool Snake::HasLost() { return m_lost;  }

void Snake::Lose() { m_lost = true; }

void Snake::ToggleLost() { m_lost = !m_lost; }

void Snake::GameOver(Textbox* text)
{
    text->Add("\n          Game Over!");
    text->Add("            Press 'R'");
    text->Add("            Score: " + std::to_string((long long)getScore()));
}

Direction Snake::CheckingDirectionIsValid()
{
    if (m_snakeBody.size() <= 1) { Direction::None; }

    SnakeSegment& head = m_snakeBody[0];
    SnakeSegment& bone = m_snakeBody[1];

    //Verifica se nos lados a um osso, se tem essa direção é invalida 
    if (head.position.y == bone.position.y) 
    {
        return head.position.x < bone.position.x ? Direction::Left : Direction::Right;
    }

    //Verifica se em cima ou em baixo a um osso, se tem essa direção é invalida 
    else if (head.position.x == bone.position.x)
    {
        return head.position.y < bone.position.y ? Direction::Up : Direction::Down;
    }

    return Direction::None;
}