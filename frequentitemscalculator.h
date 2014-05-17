#pragma once

#include "types.h"
#include "itemset.h"
#include <list>
#include <iostream>

using namespace std;

class ExtendedIdListItemSet {
private:
    list<ItemSet> _itemSets;

    void createExtendedIdListItemSet(ItemSet itemSet, ItemSet innerItemSet);
    void createPreviousNextItemSet(ItemSet itemSet, ItemSet innerItemSet);
public:
    unsigned int support;
    SequenceEventPairs sequenceEventPairs;

    ExtendedIdListItemSet(unsigned int support = 0) : support(support), sequenceEventPairs(SequenceEventPairs()) {}
    ExtendedIdListItemSet(list<ItemSet> const &itemSets) : _itemSets(itemSets), support(0), sequenceEventPairs(SequenceEventPairs()) {}
    ExtendedIdListItemSet(SequenceID sequenceId, ItemSet itemSet, EventID eventID, ItemSet innerItemSet, EventID innerEventID);

    list<ItemSet> const &itemSets() const {
        return _itemSets;
    }

    bool operator==(const ExtendedIdListItemSet &extendedIdListItemSet) const {
        bool itemSetsEqual = _itemSets == extendedIdListItemSet._itemSets;
        if (_itemSets.size() <= 1) return itemSetsEqual;
        if (sequenceEventPairs.size() != extendedIdListItemSet.sequenceEventPairs.size()) return false;
        bool eventIDsEqual = true;
        auto lit = begin(sequenceEventPairs);
        auto rit = begin(extendedIdListItemSet.sequenceEventPairs);
        for (; lit != end(sequenceEventPairs); lit++, rit++) {
            eventIDsEqual = eventIDsEqual && lit->second == rit->second;
        }
        return itemSetsEqual && eventIDsEqual;
    }

    friend ostream &operator<<(ostream &os, const ExtendedIdListItemSet &idListItemSet) {
        os << "support: " << idListItemSet.support << ", itemSets: ";
        for (const auto &itemSet : idListItemSet.itemSets()) {
            os << "[" << itemSet << "], ";
        }
        for (const auto &sequenceEventPair : idListItemSet.sequenceEventPairs) {
            os << "(" << sequenceEventPair.first << "," << sequenceEventPair.second << "), ";
        }
        return os;
    }
};

class FrequentItemsCalculator {
private:
    unsigned int _minSupport;

    bool itemExistsInInnerSets(ExtendedIdListItemSet idListItemSet, list<ExtendedIdListItemSet> innerSets);
public:
    FrequentItemsCalculator(unsigned int minSupport);
    IdListItemSets oneFrequentItems(IdListItemSets &allItems);
    list<ExtendedIdListItemSet> twoFrequentItems(IdListSequenceSets idListSequenceSets);
};
