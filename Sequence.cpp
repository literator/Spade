#include "Sequence.h"

Sequence::Sequence(SequenceID sequenceID)
        : _sequenceID(sequenceID), _itemEventPairs(ItemEventPairs()) {}

Sequence::~Sequence() {
    _itemEventPairs.clear();
}

void Sequence::addPair(ItemEventPair pair) {
    _itemEventPairs.push_back(pair);
}
