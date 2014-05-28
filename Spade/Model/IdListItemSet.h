#pragma once

#include <iostream>
#include "../Types.h"
#include "AtomSet.h"

using namespace std;

class IdListItemSet {
private:
    AtomSet _itemSet;
    SequenceEventPairs _sequenceEventPairs;
public:
    unsigned int support;

    IdListItemSet();
    IdListItemSet(Atom);
    IdListItemSet(AtomSet);
    IdListItemSet(IdListItemSet *);
    IdListItemSet(const IdListItemSet &);
    ~IdListItemSet();

    AtomSet const &itemSet() {
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
