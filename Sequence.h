#pragma once

#include "types.h"
#include <list>

using namespace std;

class Sequence {
private:
    SequenceID _sequenceID;
    ItemEventPairs _itemEventPairs;
public:
    Sequence(SequenceID);
    ~Sequence();

    SequenceID sequenceID() const { return _sequenceID; }
    ItemEventPairs pairs() { return _itemEventPairs; }
    void addPair(ItemEventPair);
};
