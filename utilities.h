#ifndef UTILITIES_H
#define UTILITIES_H

#include "Types.h"
#include <sstream>
#include <cstring>
#include <list>
#include <algorithm>
#include <vector>
#include <cctype>

namespace Utilities
{
    void stringToUpper(std::string&);
    std::string toUpper(const std::string&);

    void stringTrim(std::string&);
    std::string trim(const std::string&);

    bool stringsEqual(const std::string&, const std::string&);
    bool listsEqual(const std::list<std::string>&, const std::list<std::string>&);

    std::vector<std::string> splitToVector(const std::string& s, const char delim, const bool dsd = false);
    std::list<std::string> splitToList(const std::string& s, const char delim, const bool dsd = false);
    vector<string> removeEmptyElems(const std::vector<std::string> &);
    bool isInteger(const std::string& s);
    bool isMapValue(const std::string& );

    int  stringToInt(const std::string& s);
    MapValue stringToMapValue(const std::string& s);

    std::string intToString(const int i);
    std::string mapValueToString(const MapValue mv);
    std::string replaceSubstring(const std::string& base, const std::string& toReplace, const std::string& replaceWith);

    bool checkListSorted(const std::list<int>&, bool ascending = true);
    bool checkListUnique(const std::list<std::string>& list);
    bool checkListElemExists(const std::list<std::string>& list, const std::string& elem);

    bool checkFileReadable(const char* fileName);
    bool checkFileWritable(const char* fileName);
}

#endif // UTILITIES_H
