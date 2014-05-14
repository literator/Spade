#pragma once

#include "types.h"
#include "itemset.h"
#include <list>
#include <iostream>

typedef pair<ItemSet, EventID> ItemSetEventPair;
typedef list<ItemSetEventPair> ItemSetEventPairs;

using namespace std;

class IdListSequenceSet {
private:
    SequenceID _sequenceID;
    ItemSetEventPairs _itemEventPairs;
public:
    IdListSequenceSet(SequenceID);
    IdListSequenceSet(IdListSequenceSet *);
    ~IdListSequenceSet();

    SequenceID sequenceID() const { return _sequenceID; }
    ItemSetEventPairs pairs() const { return _itemEventPairs; }
    void addPair(ItemSetEventPair);

    friend ostream& operator<<(ostream& os, const IdListSequenceSet& sequenceSet)
    {
        uint index = 0;
        os << "sequenceSet[" << sequenceSet.sequenceID() << "]: {";
        for(const auto pair : sequenceSet.pairs())
        {
            if(index != 0) { os << ", "; }
            os << "(" << pair.first << "," << pair.second << ")";
            index++;
        }
        os << "}";
        return os;
    }
};
