#include "idlistitem.h"

IdListItemSet::IdListItemSet() : _itemSet(ItemSet()), _sequenceEventPairs(SequenceEventPairs()), support(0) {}

IdListItemSet::IdListItemSet(Item item) : _itemSet(ItemSet()), _sequenceEventPairs(SequenceEventPairs()), support(0)
{
    _itemSet.addItem(item);
}

IdListItemSet::IdListItemSet(ItemSet itemSet) :  _itemSet(itemSet), _sequenceEventPairs(SequenceEventPairs()), support(0)  {}

IdListItemSet::IdListItemSet(IdListItemSet *item)
{
    this->support = item->support;
    this->_itemSet = item->_itemSet;
    this->_sequenceEventPairs = item->_sequenceEventPairs;
}

IdListItemSet::IdListItemSet(const IdListItemSet &item)
{
    this->_itemSet = item._itemSet;
    this->_sequenceEventPairs = item._sequenceEventPairs;
}

IdListItemSet::~IdListItemSet()
{
    _sequenceEventPairs.clear();
}

void IdListItemSet::addPair(SequenceEventPair pair)
{
    _sequenceEventPairs.push_back(pair);
}



