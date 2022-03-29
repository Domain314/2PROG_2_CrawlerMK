#include <math.h>
#include <iostream>
#include "Player.hpp"

Player::Player(char name) {
    Vector2* pos = new Vector2(PLAYER_START_X, PLAYER_START_Y);
    this->entity = new Entity(name, pos);
    this->skills = new Vector3();
    resetPlayer(name);
}

Player::~Player() {
    delete entity;
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        delete inventory[i];
    }
}

char Player::chooseName() {
    char name;
    std::cout << "Choose a letter (name): ";
    std::cin >> name;
    return name;
}

void Player::resetPlayer(char name) {
    this->entity->setPos(0,0);
    this->health = PLAYER_START_HEALTH;
    this->alive = true;
    this->relics = 0;
    this->totalDamage = 0;
    this->totalHealing = 0;
    this->totalEnemies = 0;
    this->skills->setAllSides(0,0,0);
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        this->inventory[i] = new Item();
    }
}

void Player::nextLevel() {
    this->entity->setPos(0,0);
    this->health = PLAYER_START_HEALTH;
    this->alive = true;
    this->relics = 0;
}

void Player::addItem(Item *item) {
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        if (inventory[i]->getName() == "-") {
            delete inventory[i];
            inventory[i] = item;
            break;
        }
    }
}

Item* Player::getItem(int index) {
    return inventory[index];
}

void Player::passItemTurn() {
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        inventory[i]->passTurn();
    }
}

// reset all stats and calculated from inventory
void Player::updateStats() {
    skills->setAllSides(0,0,0);
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        Vector3* att = inventory[i]->getAttribute();
        skills->x += att->x;
        skills->y += att->y;
        skills->z += att->z;
    }
}

int Player::getSkill(int skill) {
    return skills->getSideFromIndex(skill);
}

void Player::changeHealth(int amount) {
    health += amount;
    if (signbit(amount)) { addTotalDamage(amount); }
    else { addTotalHealing(amount); }
    alive = (health > 0);
}

int Player::getHealth() {
    return health;
}

void Player::addRelic() {
    relics++;
}

int Player::getRelics() {
    return relics;
}

void Player::addTotalDamage(int amount) {
    totalDamage -= amount;
}

int Player::getTotalDamage() {
    return totalDamage;
}

void Player::addTotalHealing(int amount) {
    totalHealing += amount;
}

int Player::getTotalHealing() {
    return totalHealing;
}

void Player::addTotalEnemies() {
    totalEnemies++;
}

int Player::getTotalEnemies() {
    return totalEnemies;
}

bool Player::isAlive() {
    return alive;
}

Vector2* Player::getPos() {
    return entity->getPos();
}

char Player::getName() {
    return entity->getName();
}




