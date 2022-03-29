#include <string>
#include <iostream>
#include <cstdlib>
#include "Crawler/Player.hpp"
#include "Crawler/Game.hpp"

void printIntroduction() {
    std::cout << "Welcome!\n\n0. Move with WASD \n1. Get all relics (?) \n2. avoid danger (#) \n3. avoid enemies (x/+) \n4. Heal at (o) \n\nGood Luck!\n" << std::endl;
}

int main() {
    printIntroduction();
    Player* player = new Player();

    // difficulty = enemy amount
    int difficulty = ENEMY_START_AMOUNT;

    while (true) {
        Game* game = new Game(player, difficulty);

        // game loops and returns true for win, false for lose
        if (game->gameLoop()) {
            if (player->isAlive()) {
                player->nextLevel();
                difficulty *= 1.5;
            } else {
                player->resetPlayer(player->getName());
            }

        } else {
            if (game->askToReloadOrQuit(player)) {
                player->resetPlayer(player->getName());
            } else {
                delete game;
                break;
            }
        }
    }
    delete player;
    exit(0);
    return 0;
}
