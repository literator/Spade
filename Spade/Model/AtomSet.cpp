#include "AtomSet.h"
#include <iostream>

AtomSet::AtomSet() : _atoms(AtomList()) {
}

AtomSet::AtomSet(AtomList items) {
    _atoms = items;
}

AtomSet::~AtomSet() {
    _atoms.clear();
}

void AtomSet::addAtom(Atom atom) {
    _atoms.push_back(atom);
}

void AtomSet::removeAtom(Atom atom) {
    auto it = find(begin(_atoms), end(_atoms), atom);
    _atoms.erase(it);
}

bool AtomSet::atomExists(Atom atom) const {
    return find(begin(_atoms), end(_atoms), atom) != end(_atoms);
}

AtomSet::AtomSet(const AtomSet &itemSet) {
    this->_atoms = itemSet._atoms;
}

AtomSet::AtomSet(const AtomSet *itemSet) {
    this->_atoms = itemSet->_atoms;
}
