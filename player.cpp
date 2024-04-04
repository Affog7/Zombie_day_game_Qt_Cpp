#include "player.h"
#include "game.h"
#include <cmath>

Player::Player() : Character(100,0,0) // int health, int attack, int defense
{
    m_name = "player";
}

void Player::update()
{
    if (m_thrust)
    {
        m_dx += cos(m_angle * Game::DEGTORAD)*0.2;
        m_dy += sin(m_angle * Game::DEGTORAD)*0.2;
    }
    else
    {
        m_dx *= 0.99;
        m_dy *= 0.99;
    }

    int maxSpeed=15;
    float speed = sqrt(m_dx*m_dx + m_dy*m_dy);
    if (speed>maxSpeed)
    {
        m_dx *= maxSpeed/speed;
        m_dy *= maxSpeed/speed;
    }

    m_x += m_dx;
    m_y += m_dy;

    if (m_x>Game::RESOLUTION.width())
    {
        m_x = 0;
    }
    if (m_x < 0)
    {
        m_x = Game::RESOLUTION.width();
    }
    if (m_y > Game::RESOLUTION.height())
    {
        m_y = 0;
    }
    if (m_y<0)
    {
        m_y = Game::RESOLUTION.height();
    }
}
