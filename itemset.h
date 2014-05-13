#pragma once

#include <list>
#include <iostream>
#include "types.h"

using namespace std;

class ItemSet
{
private:
    ItemList _items;
public:
    ItemSet();
    ItemSet(ItemList);
    ~ItemSet();

    void addItem(Item item);
    void removeItem(Item item);

    bool itemExists(Item item);
    ItemList items() const { return _items; }


    friend ostream& operator<<(ostream& os, const ItemSet& itemSet)
    {
        uint index = 0;
        os << "itemSet: {";
        for(const auto item : itemSet.items())
        {
            if(index != 0) { os << ", "; }
            os << item;
            index++;
        }
        os << "}";
        return os;
    }
};
