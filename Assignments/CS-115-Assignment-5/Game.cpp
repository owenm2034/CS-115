// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#include "Game.h"

bool Game::isInvariantTrue() const {
    if (!world.isValid(playerLocation)) {
        cout << "The player location is invalid" << endl;
        return false;
    }
    return true;
}

Game::Game(const std::string &game_name) :
        itemManager(game_name), world(game_name), playerLocation(world.getStart()) {
    assert(isInvariantTrue());
}

bool Game::isOver() const {
    assert(isInvariantTrue());
    if (world.isVictory(playerLocation) || world.isDeath(playerLocation)) {
        return true;
    }
    return false;
}

void Game::printStartMessage() const {
    assert(isInvariantTrue());
    world.printStartMessage();
}

void Game::printEndMessage() const {
    assert(isInvariantTrue());
    world.printEndMessage();
}

void Game::printDescription() const {
    assert(isInvariantTrue());
    world.printDescription(playerLocation);
    itemManager.printAtLocation(playerLocation);
}

void Game::printInventory() const {
    assert(isInvariantTrue());
    itemManager.printInventory();
}

void Game::printScore() const {
    assert(isInvariantTrue());
    cout << "Your total score was: " << itemManager.getScore() << endl;
}

void Game::reset() {
    assert(isInvariantTrue());
    playerLocation = world.getStart();
    itemManager.reset();
    assert(isInvariantTrue());
}

void Game::moveNorth() {
    assert(isInvariantTrue());
    if (world.canGoNorth(playerLocation)) {
        playerLocation = world.getNorth(playerLocation);
        printDescription();
    } else
        cout << "You can not move in that direction" << endl;
    assert(isInvariantTrue());
}

void Game::moveSouth() {
    assert(isInvariantTrue());
    if (world.canGoSouth(playerLocation)) {
        playerLocation = world.getSouth(playerLocation);
        printDescription();
    } else
        cout << "You can not move in that direction" << endl;
    assert(isInvariantTrue());
}

void Game::moveEast() {
    assert(isInvariantTrue());
    if (world.canGoEast(playerLocation)) {
        playerLocation = world.getEast(playerLocation);
        printDescription();
    } else
        cout << "You can not move in that direction" << endl;
    assert(isInvariantTrue());
}

void Game::moveWest() {
    assert(isInvariantTrue());
    if (world.canGoWest(playerLocation)) {
        playerLocation = world.getWest(playerLocation);
        printDescription();
    } else
        cout << "You can not move in that direction" << endl;
    assert(isInvariantTrue());
}

void Game::leaveItem(char id) {
    assert(isInvariantTrue());
    itemManager.leave(id, playerLocation);
    assert(isInvariantTrue());
}

void Game::takeItem(char id) {
    assert(isInvariantTrue());
    itemManager.take(id, playerLocation);
    assert(isInvariantTrue());
}

void Game::updateScoreTable(string name) {
    scoreTable.insert(name, itemManager.getScore());
    scoreTable.print();
}