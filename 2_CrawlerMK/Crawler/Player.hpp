#ifndef CRAWLER_PLAYER_HPP
#define CRAWLER_PLAYER_HPP

#include "../Domain/globals.hpp"
#include "Entity.hpp"
#include "Item.hpp"

class Player {
public:
    explicit Player(char name = chooseName());
    ~Player();
    void resetPlayer(char name);
    void nextLevel();

    void addItem(Item* item);
    void passItemTurn();
    Item* getItem(int index);
    void updateStats();
    int getSkill(int skill);

    void changeHealth(int amount);
    int getHealth();
    void addRelic();
    int getRelics();

    void addTotalDamage(int amount);
    int getTotalDamage();
    void addTotalHealing(int amount);
    int getTotalHealing();
    void addTotalEnemies();
    int getTotalEnemies();

    bool isAlive();
    Vector2* getPos();
    char getName();




private:
    Entity* entity;
    int health;
    int relics;
    Vector3* skills;
    Item* inventory[MAX_INVENTORY];
    int totalDamage;
    int totalHealing;
    int totalEnemies;
    bool alive;
    static char chooseName();

};


#endif //CRAWLER_PLAYER_HPP
