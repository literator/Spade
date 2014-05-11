#include "itemset.h"
#include <iostream>

ItemSet::ItemSet() : _items(ItemList()) {}

ItemSet::ItemSet(ItemList items)
{
    _items = items;
}

ItemSet::~ItemSet()
{
    _items.clear();
}

void ItemSet::addItem(Item item)
{
    _items.push_back(item);
}

void ItemSet::removeItem(Item item)
{
    _items.remove(item);
}

bool ItemSet::itemExists(Item item)
{
    return find(begin(_items), end(_items), item) != end(_items);
}
