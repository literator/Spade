#pragma once

#include "../Types.h"
#include "../Model/Transaction.h"
#include "../DataReading/FileManagement.h"

using namespace std;

class DataReader
{
public:
    DataReader();
    TransactionList readTransactions(InputReader& input);
    Transaction readTransaction(const string& line);
};
