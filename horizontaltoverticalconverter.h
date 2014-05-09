#ifndef HORIZONTALTOVERTICALCONVERTER_H
#define HORIZONTALTOVERTICALCONVERTER_H

#include "idlistitem.h"
#include "types.h"
#include <list>

using namespace std;

typedef shared_ptr<IdListItem> IdListItemPtr;
typedef list<IdListItemPtr> IdListItems;

class HorizontalToVerticalConverter
{
public:
    HorizontalToVerticalConverter();
    IdListItems convertTransactions(TransactionList &list);
};

#endif // HORIZONTALTOVERTICALCONVERTER_H
