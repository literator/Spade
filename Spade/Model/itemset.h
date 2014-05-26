#pragma once

#include <iostream>
#include "../Types.h"

using namespace std;

class ItemSet {
private:
    ItemList _items;
public:
    ItemSet();
    ItemSet(ItemList);
    ItemSet(const ItemSet &);
    ItemSet(const ItemSet *);
    ~ItemSet();

    void addItem(Item item);
    void removeItem(Item item);

    bool itemExists(Item item) const;

    ItemList items() const {
        return _items;
    }

    void addItemsToItemList(ItemList &itemList) {
        for (auto item : _items) {
            itemList.push_back(item);
        }
    }

    bool operator==(const ItemSet &itemSet) const {
        return _items == itemSet._items;
    }

    bool operator>(const ItemSet &itemSet) const {
        return _items > itemSet._items;
    }

    bool operator<(const ItemSet &itemSet) const {
        return _items < itemSet._items;
    }

    friend ostream &operator<<(ostream &os, const ItemSet &itemSet) {
        static char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
        uint index = 0;
        os << "itemSet: {";
        for (const auto item : itemSet.items()) {
            if (index != 0) {os << ", ";}
            os << alphabet[item - 1];
            index++;
        }
        os << "}";
        return os;
    }
};
