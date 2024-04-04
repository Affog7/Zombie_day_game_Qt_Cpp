#ifndef ZOMBIEDAY_H
#define ZOMBIEDAY_H
#include "entity.h"
#include "character.h"
class Zombieday : public Entity, public Character
{
public:
    Zombieday();
    virtual void update() override;
};

#endif // ZOMBIEDAY_H
