#include <unistd.h>
#include <termios.h>

#include <chrono>

#include <iostream>
#include <string>
#include "Game.hpp"

Game::Game(Player *player, int difficulty) {
    this->player = player;
    error = false;
    this->difficulty = difficulty;
    this->dictionary = new Dictionary();
    setupGame();
}

Game::~Game() {
    //delete player;
    for (int i = 0; i < difficulty; ++i) {
        delete enemies.at(i);
    }
    delete dictionary;
}

// print display and start move, after valid player input. or quit game
// return true, to reload game with higher difficulty
// return false, to end game
bool Game::gameLoop() {
    while (player->isAlive()) {
        printDisplay();
        char choice = getch();
        switch (choice) {
            case 'W':
            case 'w': playerMove(0, -1); break;
            case 'A':
            case 'a': playerMove(-1, 0); break;
            case 'S':
            case 's': playerMove(0, 1); break;
            case 'D':
            case 'd': playerMove(1, 0); break;
                //case 'n': return true;
                //case 'c': return false;
            default: break;
        }
        if (error) {
            return askToReloadOrQuit(player);
        }
    }
    endGame(false);
    return false;
}

// return true for next/restart level, false for quit
bool Game::askToReloadOrQuit(Player* player) {
    char choice;
    while (true) {
        if (player->isAlive()) {
            std::cout << "\n\nNext Level: press 'N' ";
        } else {
            std::cout << "\n\nRestart Level: press 'R' ";
        }
        std::cout << "\nQuit: press 'C'" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 'R':
            case 'r':
            case 'N':
            case 'n': return true; break;
            case 'C':
            case 'c': return false; break;
            default: break;
        }
    }
}

// end and summarize the game
void Game::endGame(bool outcome) {
    error = true;
    std::cout << "\033c";
    if (outcome) {
        std::cout << "YOU WIN!";
    } else {
        std::cout << "YOU LOST!";
    }
    std::cout << "\n\nSummary:\n";
    std::cout << "Relics: " << player->getRelics() << "/" << maxRelics;
    std::cout << "\nHealth: " << player->getHealth();
    std::cout << "\nTotal healing: " << player->getTotalHealing();
    std::cout << "\nTotal damage: " << player->getTotalDamage();
    std::cout << "\nTotal enemy contact: " << player->getTotalEnemies();
    std::cout << "\nLast position: " << player->getPos()->x << ":" << player->getPos()->y;
}

// setup map and initialize next step
void Game::setupGame() {
    srand(time(NULL));
    while (maxRelics < 1) {
        maxRelics = 0;
        for (int y = 0; y < MAX_Y; y++) {
            for (size_t x = 0; x < MAX_X; x++) {
                if (x == PLAYER_START_X && y == PLAYER_START_Y) {
                    grid[x][y] = '.';
                } else {
                    randomTile(grid[y][x]);
                }
            }
        }
    }
    setupEnemies();
}

// decide on tile type, while generating map
void Game::randomTile(char& tile) {
    int rnd = randomNum(100);
    if (rnd < 40) {
        tile = '.'; // empty
    } else if (40 <= rnd && rnd < 50) {
        tile = 'o'; // health
    } else if (50 <= rnd && rnd < 60) {
        tile = '?'; // relic
        maxRelics++;
    } else if (60 <= rnd) {
        tile = '#'; // danger
    }
}

// setup enemies
void Game::setupEnemies() {
    for (int i = 0; i < difficulty; i++) {
        Enemy* enemy = new Enemy(player->getPos());
        enemies.push_back(enemy);
    }
}

// calcualte and print display.
// "auto start.. ..duration.count()" = timer for testing
void Game::printDisplay() {
    auto start = std::chrono::high_resolution_clock::now();

    // clearing console only works for Linux/Unix and window10-TH2 or higher.
    std::cout << "\033c";
    std::cout << MAGENTA << "#" << RESET << " = trap || ";
    std::cout << BOLDRED << "+" << RESET << "/" << BOLDRED << "x" << RESET << "/" << BOLDRED << "1" << RESET << "-" << BOLDRED << "9" << RESET << "/" << BOLDRED << "X" << RESET << " = enemies\n";
    std::cout << BOLDYELLOW << "?" << RESET << " = relic || " << BLUE << "o" << RESET << "= health" << std::endl;
    printMap();
    std::cout << "Health: ";
    if (player->getHealth() >= 4) {
        std::cout << CYAN << player->getHealth() << RESET;
    } else if (player->getHealth() < 4) {
        std::cout << RED << player->getHealth() << RESET;
    }
    std::cout << " || Relics: " << player->getRelics() << "/" << maxRelics << " || Enemies: " << enemies.size() << std::endl;
    printLine();
    printInventory();
    printLine();
    std::cout << getLastMessage() << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;
}

// draw map (grid)
void Game::printMap() {
    printLine();
    for (int y = 0; y < MAX_Y; y++) {
        std::cout << "|";
        for (int x = 0; x < MAX_X; x++) {
            char enemyName = getEnemyOnPos(x, y);
            if (player->getPos()->x == x && player->getPos()->y == y) {
                std::cout << WHITE << player->getName() << RESET << ' ';
            } else if (enemyName != '-') {
                std::cout << BOLDRED <<  enemyName << RESET << ' ';
            } else {
                char symbol = grid[y][x];
                //std::cout << getColouredTile(grid[y][x]) << RESET << ' ';
                switch (grid[y][x]) {
                    case 'o': std::cout << BLUE << symbol << RESET << ' '; break;
                    case '#': std::cout << MAGENTA << symbol << RESET << ' '; break;
                    case '?': std::cout << YELLOW << symbol << RESET << ' '; break;
                    case '.': std::cout << BOLDBLACK << symbol << RESET << ' '; break;
                    default: break;
                }
            }

        }
        std::cout << "|" << std::endl;
    }
    printLine();
}

// print ceiling and floor of grid-display
void Game::printLine() {
    for (size_t i = 0; i < MAX_X; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
}

// list all items in players inventory
void Game::printInventory() {
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        if (player->getItem(i)->getName()[0] != '-'){
            Item* item = player->getItem(i);
            std::cout << player->getItem(i)->getName() << ":";
            for (int j = 0; j < 3; ++j) {
                if (item->getAttribute()->getSideFromIndex(j)) {
                    std::cout << "\t"<< dictionary->getSkillName(j) << ": +" << player->getItem(i)->getAttribute()->getSideFromIndex(j);
                }
            }
            std::cout << "\tTurns:" << player->getItem(i)->getTurn() << std::endl;
        }
    }
}

void Game::setLastMessage(std::string mes) {
    this->lastMessage = mes;
}

std::string Game::getLastMessage() {
    return lastMessage;
}

// if valid move, make turn
void Game::playerMove(int x, int y) {
    if (movePosition(x, y)) {
        makeTurn();
    }
}

// check for grid-walls
bool Game::checkMove(int i, int max) {
    return (i >= 0 && i < max);
}

// validate player move decision and change pos, if true.
// return true, if all went good.
bool Game::movePosition(int moveX, int moveY) {
    int x = player->getPos()->x + moveX;
    int y = player->getPos()->y + moveY;
    if (checkMove(x, MAX_X) && checkMove(y, MAX_Y)) {
        grid[player->getPos()->y][player->getPos()->x] = '.';
        player->getPos()->x = x;
        player->getPos()->y = y;
        return true;
    }
    return false;
}

// calculate player direction from enemy perspective and move towards him
// move on axis, where the distance is higher or don't move, if the distances are equal
void Game::enemyMove(int enemyNum) {
    int xDist = player->getPos()->x - enemies[enemyNum]->getPos()->x;
    int xAbs = abs(xDist);
    int yDist = player->getPos()->y - enemies[enemyNum]->getPos()->y;
    int yAbs = abs(yDist);
    if (yAbs >= xAbs && yAbs != 0) {
        enemies[enemyNum]->getPos()->y += (yDist / yAbs);
    } else if (yAbs < xAbs && xAbs != 0) {
        enemies[enemyNum]->getPos()->x += (xDist / xAbs);
    }
}

// return int as char: https://www.codegrepper.com/code-examples/cpp/C%2B%2B+int+to+char%2A
char Game::getEnemyOnPos(int x, int y) {
    int counter = 0, index;
    for (int i = 0; i < difficulty; i++) {
        if (enemies[i]->getPos()->x == x && enemies[i]->getPos()->y == y) {
            counter++;
            index = i;
            //return enemies[i]->getName();
        }
    }
    if (counter == 1) { return enemies[index]->getName(); }
    else if (counter > 1 && counter < 10) { return '0' + counter; }
    else if (counter >= 10) { return 'X'; }
    return '-';
}

// check all Enemies for player-contact and respawn them, if needed
void Game::respawnEnemyIfHit() {
    for (int i = 0; i < difficulty; i++) {
        if (enemies[i]->getPos()->x == player->getPos()->x && enemies[i]->getPos()->y == player->getPos()->y) {
            player->changeHealth(-1);
            player->addTotalEnemies();
            delete enemies[i];
            enemies[i] = new Enemy(player->getPos());
            setLastMessage(dictionary->getMessageSnippet(40));
        }
    }
}

// go through all turn phases
void Game::makeTurn() {
    regeneration();
    checkTile();
    enemyTurns();
    itemDecay();
    player->updateStats();
}

// for each enemy: play animation and move if it's his turn
void Game::enemyTurns() {
    for (int i = 0; i < difficulty; i++) {
        if (enemies[i]->isOnField()) {
            enemies[i]->passTurn();
            if (enemies[i]->getTurn() >= ENEMY_MAX_TURN + player->getSkill(1)) {
                enemyMove(i);
                enemies[i]->resetTurn();
            }
        } else {
            delete enemies[i];
            enemies[i] = new Enemy(player->getPos());
        }

    }
}

// regenerate players health, based on his 3. skill (regen)
void Game::regeneration() {
    player->changeHealth(player->getSkill(2));
}

void Game::itemDecay() {
    player->passItemTurn();
}

// do right function, based on the grid-symbol at player-pos
void Game::checkTile() {
    switch (grid[player->getPos()->y][player->getPos()->x]) {
        case '.': break;
        case '?': relicTile(); break;
        case '#': dangerTile(); break;
        case 'o': healingTile(); break;
        default: break;
    }
    respawnEnemyIfHit();
}


// add relic to inventory and check wether it was the last or not, to end the game
void Game::relicTile() {
    player->addRelic();
    setLastMessage(dictionary->getMessageSnippet(30));
    if (player->getRelics() >= maxRelics) {
        endGame(true);
    }
    addRandomItem(player->getRelics());
}

// 15/60 Chance to lose health on entering a danger-tile.
// Chance even lower, based on player's skill 1 (defuse)
void Game::dangerTile() {
    setLastMessage(dictionary->getMessageSnippet(10));
    if ( randomNum(60) < 15 - player->getSkill(0) ) {
        player->changeHealth(-1);
        setLastMessage( getLastMessage() + dictionary->getMessageSnippet(12) + "-1");
    } else {
        setLastMessage(getLastMessage() + dictionary->getMessageSnippet(11));
    }
}

// heal the player
void Game::healingTile() {
    Item* healingBuff = new Item("H-Buff", new Vector3(0,0,1), 4);
    player->addItem(healingBuff);
    setLastMessage(dictionary->getMessageSnippet(20));
    addRandomItem(player->getRelics());
}

// generate Item, add it to player inventory and edit UI-text-message
void Game::addRandomItem(int bonusChance) {
    int rnd = randomNum(100) + bonusChance;
    if (rnd > 75) {
        Item* item = generateItem(rnd);
        player->addItem(item);
        setLastMessage(
                getLastMessage() +
                "\n" +
                dictionary->getMessageSnippet(50) +
                item->getName() +
                dictionary->getMessageSnippet(51)
                );
    }
}

// generate random Item with fitting prefix + name from Dictionary and random stats, based on their initial "chance"
Item* Game::generateItem(int chance) {
    std::string name;
    Vector3* att;
    int turns;
    if (chance > 120) {
        name = "Epic ";
        att = new Vector3(randomNum(10),randomNum(6),randomNum(4));
        turns = randomNum(100) + 40;
    } else if (chance > 100) {
        name = "Rare ";
        att = new Vector3(randomNum(5),randomNum(2),randomNum(1));
        turns = randomNum(70) + 20;
    } else if (chance > 90) {
        name = "";
        att = new Vector3(randomNum(3),randomNum(1),randomNum(1));
        turns = randomNum(50) + 10;
    } else {
        name = "Broken ";
        att = new Vector3(randomNum(1),randomNum(1),randomNum(1));
        turns = randomNum(20);
    }
    return new Item(name + dictionary->getItemName(randomNum(10)), att, turns);
}

// get Input instantly, without pressing Enter
// src: https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
char Game::getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    //printf("%c\n", buf);
    return buf;
}

void Game::testing() {
    for (int i = 0; i < MAX_INVENTORY; ++i) {
        addRandomItem(40);
    }
}