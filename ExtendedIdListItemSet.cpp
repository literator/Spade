#include "ExtendedIdListItemSet.h"

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet *itemSet) {
    _itemSets = itemSet->_itemSets;
    support = itemSet->support;
    sequenceEventPairs = itemSet->sequenceEventPairs;
}

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet &itemSet) {
    _itemSets = itemSet._itemSets;
    support = itemSet.support;
    sequenceEventPairs = itemSet.sequenceEventPairs;
}

void ExtendedIdListItemSet::createPreviousNextItemSet(ItemSet itemSet, ItemSet innerItemSet) {
    ItemList previousItemList, nextItemList;
    itemSet.addItemsToItemList(previousItemList);
    innerItemSet.addItemsToItemList(nextItemList);
    _itemSets = {ItemSet(previousItemList), ItemSet(nextItemList)};
}

void ExtendedIdListItemSet::createExtendedIdListItemSet(ItemSet itemSet, ItemSet innerItemSet) {
    ItemList itemList;
    itemSet.addItemsToItemList(itemList);
    innerItemSet.addItemsToItemList(itemList);
    _itemSets = {ItemSet(itemList)};
}

ExtendedIdListItemSet::ExtendedIdListItemSet(SequenceID sequenceId, ItemSet itemSet, EventID eventID, ItemSet innerItemSet, EventID innerEventID)
        : support(0), sequenceEventPairs(SequenceEventPairs()) {
    EventID eventToSave;
    if (eventID == innerEventID && itemSet < innerItemSet) {
        createExtendedIdListItemSet(itemSet, innerItemSet);
        eventToSave = eventID;
    } else if (eventID < innerEventID) {
        createPreviousNextItemSet(itemSet, innerItemSet);
        eventToSave = innerEventID;
    } else if (eventID > innerEventID) {
        createPreviousNextItemSet(innerItemSet, itemSet);
        eventToSave = eventID;
    }
    sequenceEventPairs.push_back(make_pair(sequenceId, eventToSave));
}
