#include "gameobject.h"
#include <iostream>


void Potion::use() const {

    std::cout << "La potion soigne le personnage.\n";
    // Logique de soin du personnage
}

ObjectType Potion::getType() const {
    return ObjectType::Potion;
}

void Weaponn::use() const {

    std::cout << "L'arme est utilise.\n";
}

ObjectType Weaponn::getType() const {
    return ObjectType::Weaponn;
}

void Armor::use() const {
    std::cout << "L'armure est équipée, augmentant la valeur de défense.\n";
    // Logique d'augmentation de la valeur de défense du personnage
}

ObjectType Armor::getType() const {
    return ObjectType::Armor;
}
