#ifndef TYPES_H
#define TYPES_H

#include <list>
#include <string>

class Transaction;

typedef unsigned int uint;
typedef unsigned int Item;
typedef unsigned int EventID;
typedef unsigned int SequenceID;

typedef unsigned int MapValue;
typedef std::list<std::list<Transaction> > SequenceData;

typedef void(*LineProcessor)(const std::string&);

enum JoinTiming{SIMULTANEOUS, BEFORE, AFTER};

enum SeqJoinType{NONE, BASIC, DOUBLE_IN, DOUBLE_OUT, LEFT_IN, RIGHT_IN};

#endif // TYPES_H
