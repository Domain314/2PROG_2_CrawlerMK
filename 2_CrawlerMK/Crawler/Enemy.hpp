#ifndef CRAWLER_ENEMY_HPP
#define CRAWLER_ENEMY_HPP

#include "../Domain/globals.hpp"
#include "Entity.hpp"

class Enemy {
public:
    Enemy(Vector2* playerPos);
    ~Enemy();
    void resetTurn();
    void passTurn();
    int getTurn();

    Vector2* getPos();
    char getName();
    bool isOnField();

private:
    Entity* entity;
    int turn;
    bool onField;

    int calcDistance(Vector2 * pPos, Vector2* ePos);
    Vector2* calcRandomPosition(Vector2* playerPos);
};


#endif //CRAWLER_ENEMY_HPP
