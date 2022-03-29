#include <valarray>
#include "Enemy.hpp"

Enemy::Enemy(Vector2* playerPos) {
    char name = (randomNum(2) == 1) ? 'x' : '+';
    this->entity = new Entity(name, calcRandomPosition(playerPos));
    this->onField = !(entity->getPos()->x == -1 && entity->getPos()->y == -1);
    this->turn = randomNum(ENEMY_MAX_TURN);
}

Enemy::~Enemy() {
    delete entity;
}

// some pythagoras magic
int Enemy::calcDistance(Vector2 * pPos, Vector2* ePos) {
    return int(sqrt(
            (ePos->x - pPos->x)*(ePos->x - pPos->x) +
            (ePos->y - pPos->y)*(ePos->y - pPos->y)
            ));
}

// search for a good spawning position
Vector2* Enemy::calcRandomPosition(Vector2* pPos) {
    int counter = 0;
    while (true) {
        Vector2* ePos = new Vector2(randomNum(MAX_X), randomNum(MAX_Y));
        if (calcDistance(pPos, ePos) > ENEMY_MIN_DISTANCE) {
            return ePos;
        }
        delete ePos;
        if (counter++ > MAX_X + MAX_Y) { return new Vector2(-1,-1); }
    }
}

void Enemy::resetTurn() {
    turn = 0;
}

void Enemy::passTurn() {
    entity->flipName();
    turn++;
}

int Enemy::getTurn() {
    return turn;
}

Vector2* Enemy::getPos() {
    return entity->getPos();
}

char Enemy::getName() {
    return entity->getName();
}

bool Enemy::isOnField() {
    return onField;
}