#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <cstdlib>
#include "gameobject.h"
#include <iostream>
#include <ctime>


class Character
{
public:
    int health;
    int attack;
    int defense;
    std::vector<GameObject*> inventory;

public:

    Character(int health, int attack, int defense)
        : health(health), attack(attack), defense(defense) {}

    virtual ~Character() {
        for (auto obj : inventory) {
            delete obj;
        }
    }

    void attackEnemy(Character& enemy) {
        // Logique de combat
    }

    void pickUpObject(GameObject* object) {
        // Logique de ramassage d'objet
        inventory.push_back(object);
    }

    virtual void interactWithAlly(Character& ally) {
        // Logique d'interaction avec un allié
    }

    void  createRandomCharacter(Character& randomCharacter);

    friend std::ostream& operator<<(std::ostream& os, const Character& character);

    std::string toString();
    std::string  getInventory() const;

};

#endif // CHARACTER_H
