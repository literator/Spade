#include "ExtendedIdListItemSet.h"
#include <set>

ExtendedIdListItemSet::ExtendedIdListItemSet(unsigned int support)
        : _atomSets(AtomSetList()), support(support), sequenceEventPairs(SequenceEventPairs()) {
}

ExtendedIdListItemSet::ExtendedIdListItemSet(AtomSetList const &atomSets)
        : _atomSets(atomSets), support(0), sequenceEventPairs(SequenceEventPairs()) {
}

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet *itemSet) {
    _atomSets = itemSet->_atomSets;
    support = itemSet->support;
    sequenceEventPairs = itemSet->sequenceEventPairs;
}

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet &itemSet) {
    _atomSets = itemSet._atomSets;
    support = itemSet.support;
    sequenceEventPairs = itemSet.sequenceEventPairs;
}

void ExtendedIdListItemSet::createPreviousNextItemSet(AtomSet itemSet, AtomSet innerItemSet) {
    AtomList previousItemList, nextItemList;
    itemSet.addAtomsToAtomList(previousItemList);
    innerItemSet.addAtomsToAtomList(nextItemList);
    _atomSets = {AtomSet(previousItemList), AtomSet(nextItemList)};
}

void ExtendedIdListItemSet::createExtendedIdListItemSet(AtomSet itemSet, AtomSet innerItemSet) {
    AtomList itemList;
    itemSet.addAtomsToAtomList(itemList);
    innerItemSet.addAtomsToAtomList(itemList);
    _atomSets = {AtomSet(itemList)};
}

ExtendedIdListItemSet::ExtendedIdListItemSet(SequenceID sequenceId, AtomSet itemSet, EventID eventID, AtomSet innerItemSet, EventID innerEventID)
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

bool const ExtendedIdListItemSet::hasEqualElementsExcludingLast(ExtendedIdListItemSet &idListItemSet) {
    AtomList localAtoms = this->allAtomsFlattened();
    AtomList remoteAtoms = idListItemSet.allAtomsFlattened();
    for (int i = 0; i < localAtoms.size() - 1; ++i) {
        if (localAtoms[i] != remoteAtoms[i]) {
            return false;
        }
    }
    return true;
}

AtomList ExtendedIdListItemSet::allAtomsFlattened() const {
    AtomList allAtoms;
    for (AtomSet atomSet : _atomSets) {
        for (auto atom : atomSet.atoms()) {
            allAtoms.push_back(atom);
        }
    }
    return allAtoms;
}

void ExtendedIdListItemSet::recalculateSupport() {
    set<SequenceID> sequenceIDsSet;
    for (SequenceEventPair pair : sequenceEventPairs) {
        sequenceIDsSet.insert(pair.first);
    }
    this->support = sequenceIDsSet.size();
}

void ExtendedIdListItemSet::addPairIfNotExists(SequenceEventPair pair) {
    auto pairIt = find(begin(this->sequenceEventPairs), end(this->sequenceEventPairs), pair);
    if (pairIt != end(this->sequenceEventPairs)) {
        this->sequenceEventPairs.push_back(pair);
    }
}

void ExtendedIdListItemSet::addAtomToTheLatestAtomSet(Atom atom) {
    AtomSet &lastAtomSet = this->_atomSets.back();
    lastAtomSet.addAtom(atom);
}
