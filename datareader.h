#pragma once

#include <list>
#include "transaction.h"
#include "filemanagement.h"
#include "Types.h"

using namespace std;

class DataReader
{
public:
    DataReader();
    TransactionList readTransactions(InputReader& input);
    Transaction readTransaction(const string& line);
};
