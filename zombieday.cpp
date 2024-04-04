#include "zombieday.h"
#include "game.h"
Zombieday::Zombieday() : Character(100,0,0)
{
    m_dx = rand()%8-4;
    m_dy = rand()%8-4;
    m_name = "enemie";
}

void Zombieday::update()
{
    m_x += m_dx;
    m_y += m_dy;

    if (m_x>Game::RESOLUTION.width())
    {
        m_x=0;
    }
    if (m_x<0)
    {
        m_x = Game::RESOLUTION.width();
    }
    if (m_y>Game::RESOLUTION.height())
    {
        m_y = 0;
    }
    if (m_y<0)
    {
        m_y = Game::RESOLUTION.height();
    }
}

