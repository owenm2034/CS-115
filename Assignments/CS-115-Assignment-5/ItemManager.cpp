// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#include "ItemManager.h"
#include <cassert>
#include <fstream>

using namespace std;

// private
void ItemManager::load(const std::string &filename) {
    ifstream fin;
    fin.open(filename);
    string temp_string;
    fin >> item_count;
    item_ptr = new Item[item_count];
    getline(fin, temp_string);


    for (int i = 0; i < item_count; i++) {
        char id;
        unsigned int starting_location;
        int points_value;
        string world_description;
        string inventory_description;

        fin >> id >> starting_location >> points_value;
        getline(fin, temp_string);
        getline(fin, world_description);
        getline(fin, inventory_description);
        item_ptr[i] = Item(
                id,
                Location(starting_location),
                points_value,
                world_description,
                inventory_description);

        getline(fin, temp_string); // for the blanks in between
    }
}

// private
unsigned int ItemManager::find(char id) const {

    int mid;
    int low = 0;
    int high = item_count;

    while (low <= high) {
        mid = (low + high) / 2;

        if (item_ptr[mid].getId() == id)
            return mid;
        else if (item_ptr[mid].getId() < id)     // intArray[mid] < target
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NO_SUCH_ITEM;
}

void ItemManager::sort() {
    // insertion sort

    int j, insert_index;
    Item x;
    for (int i = 0; i < item_count; i++) {
        // save the element from position i in the array
        x = item_ptr[i];
        // Find the insertion point
        insert_index = 0;
        while ((insert_index < i) && item_ptr[insert_index] < x) {
            insert_index++;
        }

        // Shift the elements between here and the last sorted one
        for (j = i; j > insert_index; j--) {
            item_ptr[j] = item_ptr[j - 1];
        }
        // Store x at the insertion point
        item_ptr[insert_index] = x;
    }
}


// private
bool ItemManager::isInvariantTrue() const {
    bool isInvariant = true;
    if (item_ptr == nullptr) {
        return false;
    }
    for (int i = 0; i < item_count; i++) {
        if (!item_ptr[i].isInitialized()) {
            isInvariant = false;
        }
    }
    for (int i = 0; i < item_count - 1; i++) {
        if (!(item_ptr[i] < item_ptr[i + 1])) {
            isInvariant = false;
        }
    }
    return isInvariant;
}

ItemManager::ItemManager() {
    item_count = 0;
    item_ptr = new Item[item_count];
    assert(isInvariantTrue());
}

ItemManager::ItemManager(const string &game_name) {
    item_ptr = nullptr;
    string filename = game_name + "_items.txt";
    load(filename);
    sort();
    assert(isInvariantTrue());
}

ItemManager::ItemManager(const ItemManager &to_copy) {
    assert(to_copy.isInvariantTrue());
    item_count = to_copy.item_count;
    item_ptr = new Item[item_count];
    for (int i = 0; i < item_count; i++) {
        item_ptr[i] = to_copy.item_ptr[i];
    }
    assert(isInvariantTrue());
}

ItemManager::~ItemManager() {
    assert(isInvariantTrue());
    delete[] item_ptr;
    item_ptr = nullptr;
}

ItemManager &ItemManager::operator=(const ItemManager &to_copy) {
    assert(isInvariantTrue());
    assert(to_copy.isInvariantTrue());
    if (&to_copy != this) {
        // destroy the current instance
        delete[] item_ptr;
        item_ptr = nullptr;

        // copy everything from the passed instance
        item_count = to_copy.item_count;
        item_ptr = new Item[item_count];

        for (int i = 0; i < item_count; i++) {
            item_ptr[i] = to_copy.item_ptr[i];
        }
        assert(isInvariantTrue());
    }
    return *this;
}

unsigned int ItemManager::getCount() const {
    assert(isInvariantTrue());
    return item_count;
}

int ItemManager::getScore() const {
    assert(isInvariantTrue());
    int score = 0;
    for (int i = 0; i < item_count; i++) {
        score += item_ptr[i].getPlayerPoints(); //tally players score
    }
    return score;
}

void ItemManager::printAtLocation(const Location &location) const {
    assert(isInvariantTrue());
    for (int i = 0; i < item_count; i++) {
        // if the item is in the row & column to search
        if (item_ptr[i].isAtLocation(location)) {
            // print the item's description
            item_ptr[i].printDescription();
        } // end if
    } // end for
}

void ItemManager::printInventory() const {
    assert(isInvariantTrue());
    for (int i = 0; i < item_count; i++) {
        if (item_ptr[i].isInInventory()) {
            item_ptr[i].printDescription();
        }
    }
}

bool ItemManager::isInInventory(char id) const {
    assert(isInvariantTrue());
    int i = find(id);
    if (i == NO_SUCH_ITEM) {
        return false;
    }
    if (item_ptr[i].isInInventory()) {
        return true;
    }
    return false;
}

void ItemManager::reset() {
    assert(isInvariantTrue());
    for (int i = 0; i < item_count; i++) {
        item_ptr[i].reset();
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
    if (item_ptr[i].isAtLocation(player_location)) {
        item_ptr[i].moveToInventory();
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
    if (item_ptr[i].isInInventory()) {
        item_ptr[i].reset();
        item_ptr[i].moveToLocation(player_location);
        assert(isInvariantTrue());
        return true;
    }
    cout << "Invalid item." << endl;
    assert(isInvariantTrue());
    return false;
}