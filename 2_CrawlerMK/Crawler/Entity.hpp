#ifndef CRAWLER_ENTITY_HPP
#define CRAWLER_ENTITY_HPP

#include "../Domain/Domain.h"
using namespace Domain;

class Entity {
public:
    Entity();
    Entity(char c, Vector2* pos);
    ~Entity();

    void setPos(int x, int y);
    Vector2* getPos();
    char getName();
    void flipName();

private:
    Vector2* pos;
    char name;
};

#endif //CRAWLER_ENTITY_HPP
