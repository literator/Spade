#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>

using namespace std;

class Transaction;
class ItemSet;
class IdListItemSet;
class IdListSequenceSet;

typedef unsigned int uint;
typedef uint EventID;
typedef uint Item;
typedef uint SequenceID;
typedef uint MapValue;

typedef vector<Item> ItemList;
typedef vector<Transaction> TransactionList;

typedef pair<SequenceID, EventID> SequenceEventPair;
typedef vector<SequenceEventPair> SequenceEventPairs;

typedef shared_ptr<IdListItemSet> IdListItemSetPtr;
typedef vector<IdListItemSetPtr> IdListItemSets;

typedef shared_ptr<IdListSequenceSet> IdListSequenceSetPtr;
typedef vector<IdListSequenceSetPtr> IdListSequenceSets;

typedef void(*LineProcessor)(const string&);

#endif // TYPES_H
