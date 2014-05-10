#ifndef TYPES_H
#define TYPES_H

#include <list>
#include <string>

using namespace std;

class Transaction;
class IdListItem;

typedef unsigned int uint;
typedef unsigned int Item;
typedef unsigned int EventID;
typedef unsigned int SequenceID;
typedef unsigned int MapValue;
typedef list<Transaction> TransactionList;

typedef pair<SequenceID, EventID> IdListPair;
typedef list<IdListPair> IdListPairs;
typedef shared_ptr<IdListItem> IdListItemPtr;
typedef list<IdListItemPtr> IdListItems;

// Not directly related

typedef list<list<Transaction> > SequenceData;

typedef void(*LineProcessor)(const string&);

enum JoinTiming{SIMULTANEOUS, BEFORE, AFTER};

enum SeqJoinType{NONE, BASIC, DOUBLE_IN, DOUBLE_OUT, LEFT_IN, RIGHT_IN};

#endif // TYPES_H
