#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ObjectType.h"

class GameObject {
public:
    int qte = 0;
    virtual void use() const = 0;
    virtual ObjectType getType() const = 0;
};


// Classe pour les Potions
class Potion : public GameObject {
public:
    void use() const override;
    ObjectType getType() const override;
};

// Classe pour les Armes
class Weaponn : public GameObject {
public:
    void use() const override;
    ObjectType getType() const override;
};

// Classe pour les Armures
class Armor : public GameObject {
public:
    void use() const override;
    ObjectType getType() const override;
};
#endif // GAMEOBJECT_H
