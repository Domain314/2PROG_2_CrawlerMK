#ifndef CRAWLER_ITEM_HPP
#define CRAWLER_ITEM_HPP


#include "../Domain/Domain.h"
#include <string>

using namespace Domain;

class Item {
public:
    Item();
    Item(std::string name, Vector3* attribute, int turn);
    ~Item();
    void resetItem();

    std::string getName();
    Vector3* getAttribute();
    void passTurn();
    int getTurn();

private:
    std::string name;
    Vector3* attribute;
    int turn;
};


#endif //CRAWLER_ITEM_HPP
