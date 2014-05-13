#pragma once

#include "types.h"
#include <list>

using namespace std;

class HorizontalToVerticalConverter
{
public:
    HorizontalToVerticalConverter();
    IdListItemSets convertTransactions(TransactionList &list);
};
