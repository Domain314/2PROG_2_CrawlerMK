#ifndef CRAWLER_GAME_HPP
#define CRAWLER_GAME_HPP

#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "../Domain/globals.hpp"
#include "Dictionary.hpp"


class Game {
public:
    explicit Game(Player* player, int difficulty);
    ~Game();
    Player* player;
    std::vector<Enemy*> enemies;
    char grid[MAX_X][MAX_Y];
    Dictionary* dictionary;

    bool gameLoop();
    bool askToReloadOrQuit(Player* player);
    void printDisplay();


    void setLastMessage(std::string mes);
    std::string getLastMessage();

    void testing();

private:
    int maxRelics;
    bool error;
    int difficulty;
    std::string lastMessage;

    void setupGame();
    void randomTile(char& tile);
    void setupEnemies();

    void printMap();
    void printLine();
    void printInventory();

    void playerMove(int x, int y);
    bool checkMove(int i, int max);
    bool movePosition(int x, int y);

    void enemyMove(int enemyNum);
    char getEnemyOnPos(int x, int y);
    void respawnEnemyIfHit();

    void makeTurn();
    void enemyTurns();
    void regeneration();
    void itemDecay();

    void checkTile();
    void relicTile();
    void dangerTile();
    void healingTile();

    void addRandomItem(int bonusChance = 0);
    Item* generateItem(int chance);

    void endGame(bool outcome);

    char getch();
};


#endif //CRAWLER_GAME_HPP
