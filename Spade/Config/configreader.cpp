#include "ConfigReader.h"

using namespace std;

/**
 *	Initialize the static variables
 */
Config ConfigReader::config = Config();

/**
 *	Callback function for reading minimum support
 */
void ConfigReader::readMinSupport(const string& line){
    if (Utilities::isInteger(line) == false){
        throw string("Minimum support must be a number.");
    }
    int value = Utilities::stringToInt(line);

    if (value <= 0){
        throw string("Minimum support must be be a positive integer.");
    }

    ConfigReader::config.minSupport(value);
}

/**
 *	Callback function for reading GSP setting
 */
void ConfigReader::readGSP(const string& line){
    if (Utilities::stringsEqual(line, string("TRUE"))){
        ConfigReader::config.useGSP(true);
    }
    else if (Utilities::stringsEqual(line, string("FALSE"))){
        ConfigReader::config.useGSP(false);
    }
    else {
        throw string("Invalid option for GSP detected. Expected 'TRUE' or 'FALSE'.");
    }
}

/**
 *	Callback function for reading minimum gap
 */
void ConfigReader::readMinGap(const string& line){
    if (Utilities::isInteger(line) == false){
        throw string("Minimal gap must be a number.");
    }
    int value = Utilities::stringToInt(line);

    if (value < 0){
        throw string("Minimal gap cannot be negative.");
    }

    ConfigReader::config.minGap(value);
}


/**
 *	Callback function for reading maximum gap
 */
void ConfigReader::readMaxGap(const string& line){
    if (Utilities::isInteger(line) == false){
        throw string("Maximum gap must be a number.");
    }
    int value = Utilities::stringToInt(line);

    if (value < 0){
        throw string("Maximal gap cannot be negative.");
    }

    ConfigReader::config.maxGap(value);
}

/**
 *	Callback function for reading maximum pair time
 */
void ConfigReader::readMaxTime(const string& line){
    if (Utilities::isInteger(line) == false){
        throw string("Maximum sequence time must be a number.");
    }
    int value = Utilities::stringToInt(line);

    if (value < 0){
        throw string("Maximum sequence time cannot be negative.");
    }

    ConfigReader::config.maxTime(value);
}

/**
 *	Callback function for reading window width
 */
void ConfigReader::readWindow(const string& line){
    if (Utilities::isInteger(line) == false){
        throw string("Window size must be a number.");
    }
    int value = Utilities::stringToInt(line);

    if (value < 0){
        throw string("Windows size cannot be negative.");
    }

    ConfigReader::config.window(value);
}

/**
 *	Callback function for invalid config sections
 */
void ConfigReader::error(const string& line){
    throw string("Invalid configuration syntax.");
}

/**
 *	Define the configuration sections and assign callback functions
 */
ConfigReader::ConfigReader(){
    this->_keywordMap[string("SUPPORT")] = &ConfigReader::readMinSupport;
    this->_keywordMap[string("GSP")] = &ConfigReader::readGSP;
    this->_keywordMap[string("MIN_GAP")] = &ConfigReader::readMinGap;
    this->_keywordMap[string("MAX_GAP")] = &ConfigReader::readMaxGap;
    this->_keywordMap[string("MAX_TIME")] = &ConfigReader::readMaxTime;
    this->_keywordMap[string("WINDOW")] = &ConfigReader::readWindow;
}

/**
 *	Get the instance of the config reader.
 */
ConfigReader& ConfigReader::getInstance(){
    static ConfigReader instance;
    return instance;
}

/**
 *	Function for reading the configuration for sequence finder
 */
void ConfigReader::readConfig(InputReader& input){
    if (input.isOpened() == false) {
        throw string("Cannot access input file.");
    }

    string line;
    bool dataFound = false;
    //set the default callbakc function to error function
    void (*processLine)(const std::string&) = ConfigReader::error;

    //loop over every line of input file
    while (input.isEOF() == false){
        line = input.readLine(false);
        //if we reach data section - stop processing
        if (strcmp(line.c_str(), "DATA") == 0){
            dataFound = true;
            break;
        }

        //look for section header; if ofund adjust the callback function; else - execute the callback function with the line as a parameter
        if (this->_keywordMap.count(line) == 1){
            processLine = this->_keywordMap[line];
        }
        else {
            try{
                (*processLine)(line);
            }
            catch (string message){
                stringstream ss;
                ss << input.fileName() << " line " << input.lineNr() << " : " << message;
                throw ss.str();
            }
        }
    }
    //check if data section was found
    if (dataFound == false){
        throw string("No data section found.");
    }
    //validate the configuration
    try{
        ConfigReader::config.validate();
    }
    catch (string message){
        stringstream ss;
        ss << "The specified configuration is invalid: " << message;
        throw ss.str();
    }
    return;
}

Config ConfigReader::getConfig(){
    return this->config;
}
