#include "ItemSet.h"
#include <iostream>

ItemSet::ItemSet() : _items(ItemList()) {
}

ItemSet::ItemSet(ItemList items) {
    _items = items;
}

ItemSet::~ItemSet() {
    _items.clear();
}

void ItemSet::addItem(Item item) {
    _items.push_back(item);
}

void ItemSet::removeItem(Item item) {
    auto it = find(begin(_items), end(_items), item);
    _items.erase(it);
}

bool ItemSet::itemExists(Item item) const {
    return find(begin(_items), end(_items), item) != end(_items);
}

ItemSet::ItemSet(const ItemSet &itemSet) {
    this->_items = itemSet._items;
}

ItemSet::ItemSet(const ItemSet *itemSet) {
    this->_items = itemSet->_items;
}
