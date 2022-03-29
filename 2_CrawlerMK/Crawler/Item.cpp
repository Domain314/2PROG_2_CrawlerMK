#include "Item.hpp"

Item::Item() {
    resetItem();
}

Item::Item(std::string name, Vector3 *attribute, int turn) {
    this->name = name;
    this->attribute = attribute;
    this->turn = turn;
}

Item::~Item() {
    delete attribute;
}

void Item::resetItem() {
    this->name = '-';
    this->attribute = new Vector3();
    this->turn = 0;
}

std::string Item::getName() {
    return name;
}

Vector3* Item::getAttribute() {
    return attribute;
}

void Item::passTurn() {
    turn--;
    if (turn <= 0) {
        delete attribute;
        resetItem();
    }
}

int Item::getTurn() {
    return turn;
}