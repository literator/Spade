#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <fstream>
#include <string>
#include "Utilities.h"

/**
 *	Abstract class for file management
 */
class FileManager{
protected:
    std::string  _fileName;
    unsigned int _lineNr;
    std::fstream _file;
public:
    FileManager() : _fileName(""), _lineNr(0) {};
    ~FileManager();
    std::string fileName()	{ return _fileName; };
    unsigned int lineNr()	{ return _lineNr; };
    bool isOpened()			{ return (this->_fileName.length() != 0); };

    bool isEOF()  { return this->_file.eof(); };
    void closeFile();
};

/**
 *	Class for reading from input file
 */
class InputReader : public FileManager{
protected:
    bool _skipComments;
    bool _skipEmpty;
public:
    InputReader() {};
    ~InputReader() {};


    void openFile(const std::string& fileName, bool skipComments = true, bool skipEmpty = true);

    std::string readLine(bool trim = true, bool upcase = true);
};

/**
 *	Class for writing to output file
 */
class OutputWriter : public FileManager{
protected:
public:
    OutputWriter() {};
    ~OutputWriter() {};

    void openFile(const std::string& fileName);

    void writeLine(const std::string& line);
    void write(const std::string& text);
};

#endif // FILEMANAGEMENT_H
