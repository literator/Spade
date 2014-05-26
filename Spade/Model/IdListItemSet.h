#pragma once

#include <iostream>
#include "../Types.h"
#include "../Model/ItemSet.h"

using namespace std;

class IdListItemSet {
private:
    ItemSet _itemSet;
    SequenceEventPairs _sequenceEventPairs;
public:
    unsigned int support;

    IdListItemSet();
    IdListItemSet(Item);
    IdListItemSet(ItemSet);
    IdListItemSet(IdListItemSet *);
    IdListItemSet(const IdListItemSet &);
    ~IdListItemSet();

    ItemSet const &itemSet() {
        return _itemSet;
    }

    void addPair(SequenceEventPair pair);

    SequenceEventPairs pairs() const {
        return _sequenceEventPairs;
    }

    friend ostream &operator<<(ostream &os, const IdListItemSet &idListItemSet) {
        os << idListItemSet._itemSet << ", support: " << idListItemSet.support << ", pairs: ";
        for (const auto &pair : idListItemSet.pairs()) {
            os << "[" << pair.first << "," << pair.second << "], ";
        }
        return os;
    }
};