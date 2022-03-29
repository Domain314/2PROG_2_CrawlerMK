#include <iostream>
#include "Dictionary.hpp"

Dictionary::Dictionary() {
    this->skillNames =
            {{0, "Defuse",},
             {1, "Chrono",},
             {2, "Regen"}
             };
    this->itemNames =
            {{0, "Ring",},
             {1, "Bracelet",},
             {2, "Sock",},
             {3, "Shoe",},
             {4, "Glove",},
             {5, "Pants",},
             {6, "Shirt",},
             {7, "Cape",},
             {8, "Hat",},
             {9, "Belt",},
             {10, "Glasses",},
             };
    this->mesSnippets =
            {{10, "Trap!.. ",},
             {11, "Defused!",},
             {12, "Damage taken: ",},
             {20, "Healing Field. Regeneration increased!",},
             {30, "Relic found!",},
             {40, "An Enemy hit you.",},
             {50, "Item found! [",},
             {51, "] added to Inventory",},
             {52, "Item decayed..",}
            };
}

std::string Dictionary::getSkillName(int index) {
    return skillNames[index];
}

std::string Dictionary::getItemName(int index) {
    return itemNames[index];
}

std::string Dictionary::getMessageSnippet(int index) {
    return mesSnippets.at(index);
}