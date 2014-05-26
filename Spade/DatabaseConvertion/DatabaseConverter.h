#pragma once

#include "../Types.h"

using namespace std;

class DatabaseConverter
{
public:
    DatabaseConverter();
    IdListItemSets convertHorizontalToVertical(TransactionList &list);
    IdListSequenceSets convertVerticalToHorizontal(IdListItemSets &list);
};
