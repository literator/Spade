#include <iostream>
#include <sstream>

#include "filemanagement.h"
#include "config.h"
#include "configreader.h"
#include "datareader.h"

using namespace std;

int main(int argc, char** argv)
{
    stringstream ss;
    if (argc != 3) {
        ss << "Invalid parameter count.\nThe command to run the program  - \"" << argv[0] << " <input file path> <result file path>\".";
        cerr << ss.str() << endl;
        return 1;
    }

    InputReader input;
    OutputWriter output;
    Config config;

    try {
        input.openFile(string(argv[1]));
    }
    catch (string message) {
        ss << "Error opening input file: " << message;
        cerr << ss.str() << endl;
        return 2;
    }

    try {
        output.openFile(string(argv[2]));
    }
    catch (string message) {
        ss << "Error opening output file: " << message;
        cerr << ss.str() << endl;
        return 3;
    }

    try {
        ConfigReader cr = ConfigReader::getInstance();
        cr.readConfig(input);
        config = cr.getConfig();
    }
    catch (string message) {
        ss << "Error reading configuration: " << message;
        cerr << ss.str() << endl;
        return 4;
    }
    catch (...) {
        cerr << "Unknown error while reading the configuration." << endl;
        return 5;
    }

    DataReader dataReader;
    TransactionList transactions = dataReader.readTransactions(input);

    for (const auto &transaction : transactions)
    {
        cout << transaction << endl;
    }

    return 0;
}
