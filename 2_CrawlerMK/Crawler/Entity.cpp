#include "Entity.hpp"

Entity::Entity() {
    this->name = 'F';
    this->pos = new Vector2(0,0);
}

Entity::Entity(char c, Vector2* pos) {
    this->name = c;
    this->pos = pos;
}

Entity::~Entity() {
    delete pos;
}

void Entity::setPos(int x, int y) {
    this->pos->x = x;
    this->pos->y = y;
}

Vector2* Entity::getPos() {
    return pos;
}

char Entity::getName() {
    return name;
}

void Entity::flipName() {
    name = (name == 'x') ? '+' : 'x';
}
