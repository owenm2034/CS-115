//
// Created by Owen Monus on 2022-11-03.
//

#include "ItemManager.h"
#include <cassert>
using namespace std;

// private
unsigned int ItemManager::find(char id) const {
    for (int i = 0; i < ITEM_COUNT; i++){
        if (items[i].getId() == id) {
            return i;
        }
    }
    return NO_SUCH_ITEM;
}

// private
bool ItemManager::isInvariantTrue() const {
    bool isInvariant = true;
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (!items[i].isInitialized()) {
            isInvariant = false;
        }
    }
    return isInvariant;
}

ItemManager::ItemManager(const string &game_name) {
    items[0] = { // scarab beetle
            's',
            Location(0, 3),
            -5,
            "There is a black scarab beetle (s) here.",
            "A black scarab beetle (s) is crawling up your arm."
    };
    items[1] = { // candle stick
            'c',
            Location(1, 1),
            9,
            "There is a silver candlestick (c) here.",
            "You are carrying a silver candlestick (c)."
    };
    items[2] = { // key
            'k',
            Location(2, 0),
            3,
            "There is an old iron key (k) here.",
            "You have an old iron key (k) in your pocket."
    };
    items[3] = { // tarantula
            't',
            Location(2, 9),
            -8,
            "There is a tarantula (t) here.",
            "There is a tarantula (t) hanging on your shirt."
    };
    items[4] = { // book
            'b',
            Location(3, 4),
            4,
            "There is a book (b) here with an eye drawn on the cover.",
            "You have a book (b) under your arm with an eye drawn on the cover."
    };
    items[5] = { // moth
            'm',
            Location(5, 5),
            -2,
            "There is a giant moth (m) sleeping here.",
            "A giant moth (m) is perched on your shoulder."
    };
    items[6] = { //amulet
            'p',
            Location(7, 9),
            7,
            "There is a golden pendant (p) here.",
            "You are wearing a golden pendant (p)."
    };
    items[7] = { // dagger
            'd',
            Location(8, 0),
            1,
            "There is a rune-carved dagger (d) here.",
            "You have a rune-carved dagger (d) stuck in your belt."
    };
    items[8] = { // ring
            'r',
            Location(9, 6),
            10,
            "There is a diamond ring (r) here.",
            "You are wearing a diamond ring (r)."
    };
    assert(isInvariantTrue());
}

unsigned int ItemManager::getCount() const {
    assert(isInvariantTrue());
    return ITEM_COUNT;
}

int ItemManager::getScore() const {
    assert(isInvariantTrue());
    int score = 0;
    for (int i = 0; i < ITEM_COUNT; i++) {
        score += items[i].getPlayerPoints(); //tally players score
    }
    return score;
}

void ItemManager::printAtLocation(const Location &location) const {
    assert(isInvariantTrue());
    for (int i = 0; i < ITEM_COUNT; i++) {
        // if the item is in the row & column to search
        if (items[i].isAtLocation(location)) {
            // print the item's description
            items[i].printDescription();
        } // end if
    } // end for
}

void ItemManager::printInventory() const {
    assert(isInvariantTrue());
    for(int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].isInInventory()) {
            items[i].printDescription();
        }
    }
}

bool ItemManager::isInInventory(char id) const {
    assert(isInvariantTrue());
    int i = find(id);
    if (i == NO_SUCH_ITEM) {
        return false;
    }
    if (items[i].isInInventory()) {
        return true;
    }
    return false;
}

void ItemManager::reset() {
    assert(isInvariantTrue());
    for (int i = 0; i < ITEM_COUNT; i++) {
        items[i].reset();
    }
    assert(isInvariantTrue());
}

bool ItemManager::take(char id, const Location &player_location) {
    assert(isInvariantTrue());
    int i = find(id);
    if (i == NO_SUCH_ITEM) {
        cout << "Invalid item." << endl;
        assert(isInvariantTrue());
        return false;
    }
    if (items[i].isAtLocation(player_location)) {
        items[i].moveToInventory();
        assert(isInvariantTrue());
        return true;
    }
    cout << "Invalid item." << endl;
    assert(isInvariantTrue());
    return false;
}

bool ItemManager::leave(char id, const Location &player_location) {
    assert(isInvariantTrue());
    int i = find(id);
    if (i == NO_SUCH_ITEM) {
        cout << "Invalid item." << endl;
        assert(isInvariantTrue());
        return false;
    }
    if (items[i].isInInventory()) {
        items[i].reset();
        items[i].moveToLocation(player_location);
        assert(isInvariantTrue());
        return true;
    }
    cout << "Invalid item." << endl;
    assert(isInvariantTrue());
    return false;
}