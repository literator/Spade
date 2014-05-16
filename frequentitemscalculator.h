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

    ExtendedIdListItemSet(unsigned int support = 0) : support(support) {}
    ExtendedIdListItemSet(list<ItemSet> const &itemSets) : _itemSets(itemSets), support(0) {}
    ExtendedIdListItemSet(ItemSet itemSet, EventID eventID, ItemSet innerItemSet, EventID innerEventID);

    list<ItemSet> const &itemSets() const {
        return _itemSets;
    }

    bool operator==(const ExtendedIdListItemSet &extendedIdListItemSet) const {
        return _itemSets == extendedIdListItemSet._itemSets;
    }

    friend ostream &operator<<(ostream &os, const ExtendedIdListItemSet &idListItemSet) {
        os << "support: " << idListItemSet.support << ", itemSets: ";
        for (const auto &itemSet : idListItemSet.itemSets()) {
            os << "[" << itemSet << "], ";
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
