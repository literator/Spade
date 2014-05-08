#include "filemanagement.h"

using namespace std;

/**
 *	Function for automatic closing any open file handles
 */
FileManager::~FileManager(){
    if (this->isOpened()){
        this->closeFile();
    }
}

/**
 *	Function for closing the opened file.
 */
void FileManager::closeFile(){
    if (this->isOpened() == false){
        throw string("No opened file detected.");
    }
    this->_file.close();
    this->_fileName = "";
}

/**
 *	Function for opening file for reading
 */
void InputReader::openFile(const std::string& fileName, bool skipComments, bool skipEmpty){
    if (this->_fileName.length() != 0){
        throw string("Already opened file exists.");
    }

    this->_file.open(fileName.c_str(), ios_base::in);

    if (this->_file.is_open() == false){
        throw string("Cannot open file for reading.");
    }

    this->_fileName = fileName;
    this->_skipComments = skipComments;
    this->_skipEmpty = skipEmpty;
}

/**
 *	Function for reading a line of text from input
 */
std::string InputReader::readLine(bool trim, bool upcase){
    string result;

    while (true){
        if (_file.eof())
            break;
        //read line from file
        _lineNr++;
        getline(_file, result);

        //check if line is empty and skip it if _skipEmpty flag is set
        if (this->_skipEmpty && result.size() == 0)
            continue;
        //check if line is a comment and skip it if _skipComments flag is set (comments start with '#' sign)
        if (this->_skipComments && result.size() != 0 && result[0] == '#')
            continue;

        break;
    }
    //perform final line modifications
    if (trim)   { result = Utilities::trim(result);    }
    if (upcase) { result = Utilities::toUpper(result); }

    return result;
}

/**
 *	Function for opening file for writing
 */
void OutputWriter::openFile(const std::string& fileName){
    if (this->_fileName.length() != 0){
        throw string("Already opened file exists.");
    }

    this->_file.open(fileName.c_str(), ios_base::out);

    if (this->_file.is_open() == false){
        throw string("Cannot open file for writing.");
    }

    this->_fileName = fileName;
}

/**
 *	Function for writing given text to a file; adds a new line sign at the end
 */
void OutputWriter::writeLine(const std::string& line){
    stringstream ss;
    ss << line << "\n";
    this->_file.write(ss.str().c_str(), ss.str().length());
    if (this->_file.bad()){
        throw string("Error when writing line.");
    }
}

/**
 *	Function for writing given text to a file
 */
void OutputWriter::write(const std::string& text){
    this->_file.write(text.c_str(), text.length());
    if (this->_file.bad()){
        throw string("Error when writing text.");
    }
}
