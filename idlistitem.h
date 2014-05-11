#ifndef IDLISTITEM_H
#define IDLISTITEM_H

#include <list>
#include <iostream>
#include "types.h"
#include "itemset.h"

using namespace std;

class IdListItemSet
{
private:
    ItemSet _itemSet;
    IdListPairs _idListPairs;
public:
    unsigned int support;

    IdListItemSet();
    IdListItemSet(Item);
    IdListItemSet(ItemSet);
    IdListItemSet(IdListItemSet *);
    IdListItemSet(const IdListItemSet &);
    ~IdListItemSet();

    ItemSet itemSet() const { return _itemSet; }

    void addPair(IdListPair pair);
    IdListPairs pairs() const { return _idListPairs; }

    friend ostream& operator<<(ostream& os, const IdListItemSet& idListItemSet)
    {
        os << idListItemSet.itemSet() << ", support: " << idListItemSet.support << ", pairs: ";
        for(const auto &pair : idListItemSet.pairs())
        {
            os << "[" << pair.first << "," << pair.second << "], ";
        }
        return os;
    }
};

#endif // IDLISTITEM_H
