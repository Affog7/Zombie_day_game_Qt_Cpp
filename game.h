#ifndef GAME_H
#define GAME_H
#include <QSize>

class Entity;
class Game
{
public:
    Game();
    static bool isCollide(Entity *a,Entity *b);
    static const QSize RESOLUTION;
    static const float DEGTORAD;
    static const QString PATH_TO_BG_PIXMAP;
    static const QString PATH_TO_FIRE_BLUE_PIXMAP;
    static const QString PATH_TO_FIRE_RED_PIXMAP;
    static const QString PATH_TO_ROCK_PIXMAP;
    static const QString PATH_TO_ROCK_SMALL_PIXMAP;
    static const QString PATH_TO_SPACESHIP_PIXMAP;
    static const QString PATH_TO_SPACESHIP_GO_PIXMAP;
    static const QString PATH_TO_SPACESHIP_HELPER_PIXMAP;
    static const QString PATH_TO_EXPLOSION_A_PIXMAP;
    static const QString PATH_TO_EXPLOSION_B_PIXMAP;
    static const QString PATH_TO_EXPLOSION_C_PIXMAP;
    static const float ITERATION_VALUE;
};

#endif // GAME_H
