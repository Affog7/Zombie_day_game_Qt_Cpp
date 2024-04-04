#ifndef HELPER_H
#define HELPER_H

#include "entity.h"
#include "character.h"

class Helper : public Entity , public Character
{
public:
    Helper();
    virtual void update() override;
};

#endif // HELPER_H
