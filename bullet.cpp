#include "bullet.h"
#include "game.h"
#include <cmath>

Bullet::Bullet()
{
    m_name = "bullet";
}

void Bullet::update()
{
    m_dx = cos( m_angle * Game::DEGTORAD) * 6;
    m_dy = sin( m_angle * Game::DEGTORAD) * 6;
   // angle+=rand()%6-3;
    m_x += m_dx;
    m_y += m_dy;

    if (m_x > Game::RESOLUTION.width() || m_x<0 || m_y > Game::RESOLUTION.height() || m_y<0)
    {
      m_life = false;
    }
}
