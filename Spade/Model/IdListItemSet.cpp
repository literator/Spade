#include "IdListItemSet.h"

IdListItemSet::IdListItemSet() : _itemSet(AtomSet()), _sequenceEventPairs(SequenceEventPairs()), support(0) {}

IdListItemSet::IdListItemSet(Atom item) : _itemSet(AtomSet()), _sequenceEventPairs(SequenceEventPairs()), support(0)
{
    _itemSet.addAtom(item);
}

IdListItemSet::IdListItemSet(AtomSet itemSet) :  _itemSet(itemSet), _sequenceEventPairs(SequenceEventPairs()), support(0)  {}

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



