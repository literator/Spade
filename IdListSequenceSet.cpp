#include "IdListSequenceSet.h"

IdListSequenceSet::IdListSequenceSet(SequenceID sequenceID)
        : _sequenceID(sequenceID), _itemEventPairs(ItemSetEventPairs()) {}

IdListSequenceSet::~IdListSequenceSet() {
    _itemEventPairs.clear();
}

void IdListSequenceSet::addPair(ItemSetEventPair pair) {
    _itemEventPairs.push_back(pair);
}

IdListSequenceSet::IdListSequenceSet(IdListSequenceSet *sequenceSet) {
    this->_sequenceID = sequenceSet->_sequenceID;
    this->_itemEventPairs = sequenceSet->_itemEventPairs;
}
