#include "Utilities.h"

using namespace std;

#include <fstream>

string Utilities::toUpper(const string &s) {
    string result;
    char c;
    unsigned int length = s.length();

    for (unsigned int i = 0; i < length; i++) {
        c = s[i];
        result.push_back(toupper((unsigned char) c));
    }

    return result;
}

void Utilities::stringToUpper(string &s) {
    s = Utilities::toUpper(s);
}

string Utilities::trim(const string &s) {
    string result;
    std::string::const_iterator it, it2, end;

    it = s.begin();
    end = s.end();

    while (it != end && isspace(*it))
        it++;

    if (it == end)    //if no characters left - return empty string
        return result;

    it2 = --s.end();    //it2 points to the last character in the string
    while (it2 != it && isspace(*it2))
        it2--;

    it2++;    //move the iterator to show the position after the last character to include in result

    while (it != it2) {
        result.push_back(*it);
        it++;
    }

    return result;
}

string Utilities::replaceSubstring(const string &base, const string &toReplace, const string &replaceWith) {
    size_t index = 0;
    string result = base;
    while (true) {
        /* Locate the substring to replace. */
        index = result.find(toReplace, index);
        if (index == string::npos) break;

        /* Make the replacement. */
        result.replace(index, toReplace.size(), replaceWith);

        /* Advance index forward one spot so the next iteration doesn't pick it up as well. */
        ++index;
    }
    return result;
}

void Utilities::stringTrim(string &s) {
    s = Utilities::trim(s);
}

bool Utilities::stringsEqual(const string &s1, const string &s2) {
    return (strcmp(s1.c_str(), s2.c_str()) == 0);
}

bool Utilities::listsEqual(const std::list<std::string> &l1, const std::list<std::string> &l2) {
    list<string> difference;
    set_difference(l1.begin(), l1.end(), l2.begin(), l2.end(), difference.begin());
    return (difference.size() == 0);
}

vector<string> Utilities::splitToVector(const string &line, const char delimiter, const bool dsd) {
    vector<string> result;
    string elem;

    string::const_iterator it, end;
    bool wasDelim = false;

    for (it = line.begin(), end = line.end(); it != end; it++) {
        if (*it == delimiter) {
            if (wasDelim == false || dsd == true)
                result.push_back(elem);
            elem.clear();
            wasDelim = true;
        }
        else {
            wasDelim = false;
            elem.push_back(*it);
        }
    }

    result.push_back(elem);

    return result;
}

list<string> Utilities::splitToList(const string &line, const char delimiter, const bool dsd) {
    list<string> result;
    string elem;

    string::const_iterator it, end;
    bool wasDelim = false;

    for (it = line.begin(), end = line.end(); it != end; it++) {
        if (*it == delimiter) {
            if (wasDelim == false || dsd == true)
                result.push_back(elem);
            elem.clear();
            wasDelim = true;
        }
        else {
            wasDelim = false;
            elem.push_back(*it);
        }
    }

    result.push_back(elem);

    return result;
}

vector<string> Utilities::removeEmptyElems(const vector<string> &l) {
    vector<string>::const_iterator it, end;
    vector<string> result;

    for (it = l.begin(), end = l.end(); it != end; it++) {
        if (it->empty() == false)
            result.push_back(*it);
    }
    return result;
}

bool Utilities::checkListUnique(const list<string> &l) {
    list<string>::const_iterator base, curr, end;

    for (base = l.begin(), end = l.end(); base != end; base++) {
        for (curr = base, curr++; curr != end; curr++) {
            if (strcmp(base->c_str(), curr->c_str()) == 0)
                return false;
        }
    }

    return true;
}

bool Utilities::checkListElemExists(const list<string> &l, const string &elem) {
    list<string>::const_iterator it, end;

    for (it = l.begin(), end = l.end(); it != end; it++) {
        if (strcmp(it->c_str(), elem.c_str()) == 0)
            return true;
    }
    return false;
}

bool Utilities::isInteger(const string &s) {
    if (s.empty())
        return false;

    stringstream ss;
    ss << s;
    int i;
    ss >> i;

    return (ss.eof());
}

bool Utilities::isMapValue(const string &s) {
    if (s.empty())
        return false;

    stringstream ss;
    ss << s;
    MapValue i;
    ss >> i;

    return (ss.eof());
}

int Utilities::stringToInt(const string &s) {
    stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

MapValue Utilities::stringToMapValue(const string &s) {
    stringstream ss(s);
    MapValue i;
    ss >> i;
    return i;
}

string Utilities::intToString(const int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

string Utilities::mapValueToString(const MapValue mv) {
    stringstream ss;
    ss << mv;
    return ss.str();
}

bool Utilities::checkFileReadable(const char *fileName) {
    ifstream input(fileName);
    bool result = input.is_open();
    input.close();
    return result;
}

bool Utilities::checkFileWritable(const char *fileName) {
    ofstream input(fileName);
    bool result = input.is_open();
    input.close();
    return result;
}
