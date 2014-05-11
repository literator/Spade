#ifndef HORIZONTALTOVERTICALCONVERTER_H
#define HORIZONTALTOVERTICALCONVERTER_H

#include "types.h"
#include <list>

using namespace std;

class HorizontalToVerticalConverter
{
public:
    HorizontalToVerticalConverter();
    IdListItemSets convertTransactions(TransactionList &list);
};

#endif // HORIZONTALTOVERTICALCONVERTER_H
