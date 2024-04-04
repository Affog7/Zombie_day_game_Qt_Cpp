#ifndef BULLET_H
#define BULLET_H
#include "entity.h"

class Bullet : public Entity
{
public:
    Bullet();
    virtual void update() override;
};

#endif // BULLET_H
