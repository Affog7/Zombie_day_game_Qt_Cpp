#include "character.h"

void Character::createRandomCharacter(Character& randomCharacter)
{
        // Initialisation de la graine pour la génération aléatoire
        std::srand(static_cast<unsigned int>(std::time(nullptr)));



        // Ajout d'objets aléatoires à l'inventaire du joueur
        int numObjects = rand() % 2 +1 ;  // Nombre aléatoire d'objets entre 1 et 3

        for (int i = 0; i < numObjects; ++i) {
            // Création d'un objet aléatoire (Potion, Arme, ou Armure)
            ObjectType objectType = static_cast<ObjectType>(rand() % 3);

            // Ajout de l'objet à l'inventaire du joueur
            switch (objectType) {
            case ObjectType::Potion:
                randomCharacter.pickUpObject(new Potion());
                break;
            case ObjectType::Weaponn:
                randomCharacter.pickUpObject(new Weaponn());
                break;
            case ObjectType::Armor:
                randomCharacter.pickUpObject(new Armor());
                break;
            }
        }

}


// Overloading the << operator to display the inventory
std::ostream& operator<<(std::ostream& os, const Character& character) {
    os << "Character Stats:" << std::endl;
    os << "Health: " << character.health << std::endl;
    os << "Attack: " << character.attack << std::endl;
    os << "Defense: " << character.defense << std::endl;

    os << "Inventory:" << std::endl;
    for (const auto& obj : character.inventory) {
        os << " - " << std::to_string(static_cast<int>(obj->getType()))<< std::endl;
    }

    return os;
}


//l'inventaire
std::string Character::toString() {
    std::string result;
    result += "Character Stats:\n";
    result += "Health: " + std::to_string(health) + "\n";
    result += "Attack: " + std::to_string(attack) + "\n";
    result += "Defense: " + std::to_string(defense) + "\n";

    result += "Inventory:\n";
    result += getInventory();

    return result;
}


std::string Character::getInventory() const {
    std::string result = "";
    if(inventory.size()>=1)  {

        Potion p  ;
        Weaponn w ;
        Armor a  ;


            for(int j = 0; j<inventory.size(); j++){
                if(inventory.at(j)->getType() == ObjectType::Armor) {
                    a.qte +=1;
                }
                if(inventory.at(j)->getType() == ObjectType::Potion) {
                    p.qte +=1;
                }
                if(inventory.at(j)->getType() == ObjectType::Weaponn) {
                    w.qte +=1;
                }
            }

          result += std::to_string(static_cast<int>(p.getType()))+"->Potion :"+std::to_string(static_cast<int>(p.qte));
          result += "\n"+std::to_string(static_cast<int>(w.getType()))+"->Weaponn :"+std::to_string(static_cast<int>(w.qte));
          result += "\n"+std::to_string(static_cast<int>(a.getType()))+"->Armor :"+std::to_string(static_cast<int>(a.qte));



    }


     return result;
}
