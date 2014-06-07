#pragma once

#include <iostream>
#include "../Types.h"

//#define ALPHABET

using namespace std;

class AtomSet;

typedef vector<AtomSet> AtomSetList;

class AtomSet {
private:
    AtomList _atoms;
public:
    AtomSet();
    AtomSet(Atom);
    AtomSet(AtomList);
    AtomSet(const AtomSet &);
    AtomSet(const AtomSet *);
    ~AtomSet();

    void addAtom(Atom atom);
    void removeAtom(Atom atom);

    bool atomExists(Atom atom) const;

    AtomList const &atoms() const {
        return _atoms;
    }

    Atom const lastAtom() const {
        return _atoms.back();
    }

    int const size() const { return _atoms.size(); }

    void addAtomsToAtomList(AtomList &atomList) {
        for (auto atom : _atoms) {
            atomList.push_back(atom);
        }
    }

    bool operator==(const AtomSet &atomSet) const {
        return _atoms == atomSet._atoms;
    }

    bool operator!=(const AtomSet &atomSet) const {
        return !(*this == atomSet);
    }

    bool operator>(const AtomSet &atomSet) const {
        return _atoms > atomSet._atoms;
    }

    bool operator<(const AtomSet &atomSet) const {
        return _atoms < atomSet._atoms;
    }

    friend ostream &operator<<(ostream &os, const AtomSet &atomSet) {
#ifdef ALPHABET
        static char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
#endif
        uint index = 0;
        os << "itemSet: {";
        for (const auto item : atomSet.atoms()) {
            if (index != 0) {os << ", ";}
#ifdef ALPHABET
            os << alphabet[item - 1];
#else
            os << item;
#endif
            index++;
        }
        os << "}";
        return os;
    }
};
