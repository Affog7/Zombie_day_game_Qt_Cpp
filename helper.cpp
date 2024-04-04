#include "helper.h"
#include "game.h"
#include <cmath>

Helper::Helper() : Character(100,0,0) {
    m_name = "helper";
}

void Helper::update()
{
    // Réduction de la vitesse à 3
    m_dx = cos(m_angle * Game::DEGTORAD) * 1.5;
    m_dy = sin(m_angle * Game::DEGTORAD) * 2;

    // Mise à jour de la position en fonction de la vitesse réduite
    m_x += m_dx;
    m_y += m_dy;

    // Vérification des limites de l'écran
    if (m_x > Game::RESOLUTION.width() || m_x < 0 || m_y > Game::RESOLUTION.height() || m_y < 0)
    {
        m_life = false;
    }
}

