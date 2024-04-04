#include "game.h"
#include "entity.h"

const QSize Game::RESOLUTION = QSize(1200, 800);
const float Game::DEGTORAD = 0.017453f;

const QString Game::PATH_TO_BG_PIXMAP = ":/res/images/background.png";
const QString Game::PATH_TO_FIRE_BLUE_PIXMAP = ":/res/images/fire_blue.png";
const QString Game::PATH_TO_FIRE_RED_PIXMAP = ":/res/images/fire_red.png";
const QString Game::PATH_TO_ROCK_PIXMAP = ":/res/images/rock.png";
const QString Game::PATH_TO_ROCK_SMALL_PIXMAP = ":/res/images/rock_small.png";
const QString Game::PATH_TO_SPACESHIP_PIXMAP = ":/res/images/spaceship.png";
const QString Game::PATH_TO_SPACESHIP_HELPER_PIXMAP = ":/res/images/extra.png";
const QString Game::PATH_TO_SPACESHIP_GO_PIXMAP = ":/res/images/spaceship_go.png";
const QString Game::PATH_TO_EXPLOSION_A_PIXMAP = ":/res/images/explosions/type_A.png";
const QString Game::PATH_TO_EXPLOSION_B_PIXMAP = ":/res/images/explosions/type_B.png";
const QString Game::PATH_TO_EXPLOSION_C_PIXMAP = ":/res/images/explosions/type_C.png";

const float Game::ITERATION_VALUE = 1000.0f/60.0f;

Game::Game()
{

}

bool Game::isCollide(Entity *a,Entity *b)
{
  return (b->m_x - a->m_x)*(b->m_x - a->m_x)+
         (b->m_y - a->m_y)*(b->m_y - a->m_y)<
         (a->m_R + b->m_R)*(a->m_R + b->m_R);
}
