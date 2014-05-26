#pragma once

#include "../Types.h"
#include "ItemSet.h"

using namespace std;

class ExtendedIdListItemSet {
private:
    vector<ItemSet> _itemSets;

    void createExtendedIdListItemSet(ItemSet itemSet, ItemSet innerItemSet);
    void createPreviousNextItemSet(ItemSet itemSet, ItemSet innerItemSet);
public:
    unsigned int support;
    SequenceEventPairs sequenceEventPairs;

    ExtendedIdListItemSet(unsigned int support = 0) : support(support), sequenceEventPairs(SequenceEventPairs()) {
    }

    ExtendedIdListItemSet(vector<ItemSet> const &itemSets)
            : _itemSets(itemSets), support(0), sequenceEventPairs(SequenceEventPairs()) {
    }

    ExtendedIdListItemSet(SequenceID sequenceId, ItemSet itemSet, EventID eventID, ItemSet innerItemSet, EventID innerEventID);

    ExtendedIdListItemSet(const ExtendedIdListItemSet &);
    ExtendedIdListItemSet(const ExtendedIdListItemSet *);

    vector<ItemSet> const &itemSets() const {
        return _itemSets;
    }

    bool operator==(const ExtendedIdListItemSet &extendedIdListItemSet) const {
        bool itemSetsEqual = _itemSets == extendedIdListItemSet._itemSets;
//        if (_itemSets.size() <= 1) return itemSetsEqual;
//        if (sequenceEventPairs.size() != extendedIdListItemSet.sequenceEventPairs.size()) return false;
//        bool eventIDsEqual = true;
//        auto lit = begin(sequenceEventPairs);
//        auto rit = begin(extendedIdListItemSet.sequenceEventPairs);
//        for (; lit != end(sequenceEventPairs); lit++, rit++) {
//            eventIDsEqual = eventIDsEqual && lit->second == rit->second;
//        }
//        return itemSetsEqual && eventIDsEqual;
        return itemSetsEqual;
    }

    bool operator<(const ExtendedIdListItemSet *extendedIdListItemSet) const {
        return _itemSets < extendedIdListItemSet->_itemSets;
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
