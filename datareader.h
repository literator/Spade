#ifndef DATAREADER_H
#define DATAREADER_H

#include <list>
#include "transaction.h"
#include "filemanagement.h"

typedef std::list<Transaction> TransactionList;

using namespace std;

class DataReader
{
public:
    DataReader();
    TransactionList readTransactions(InputReader& input);
    Transaction readTransaction(const string& line);
};

#endif // DATAREADER_H
