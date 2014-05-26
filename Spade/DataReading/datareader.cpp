#include "DataReader.h"
#include "../Utilities/Utilities.h"

DataReader::DataReader() {
}

TransactionList DataReader::readTransactions(InputReader &input) {
    string line;
    TransactionList result;
    try {
        while (input.isEOF() == false) {
            line = input.readLine();
            if (line != "") {
                result.push_back(readTransaction(line));
            }
        }
    }
    catch (string message) {
        stringstream ss;
        ss << input.fileName() << " line " << input.lineNr() << " : " << message;
        throw ss.str();
    }
    return result;
}

Transaction DataReader::readTransaction(const string &line) {
    vector<string> stringTokens = Utilities::splitToVector(line, ' ');
    stringTokens = Utilities::removeEmptyElems(stringTokens);

    if (stringTokens.size() < 3) {
        throw string("Transaction line must have at least 3 elements: client_id, timestamp and an atom.");
    }

    list<MapValue> tokens;

    //check whether the values of tokens are valid
    for (auto sit = begin(stringTokens); sit != end(stringTokens); sit++) {
        if (!Utilities::isMapValue(*sit)) {
            throw string("All elements in transaction line must be a number.");
        }
        tokens.push_back(Utilities::stringToMapValue(*sit));
    }

    SequenceID sequenceID = tokens.front();
    tokens.pop_front();
    EventID eventID = tokens.front();
    tokens.pop_front();

    vector<MapValue> tokensVector{make_move_iterator(begin(tokens)), make_move_iterator(end(tokens))};
    Transaction t(sequenceID, eventID, tokensVector);
    return t;
}
