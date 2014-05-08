#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include "Types.h"
#include "Config.h"
#include "FileManagement.h"
#include <string>
#include <map>

/**
 *	Class for reading the configuration file for sequence finder
 */
class ConfigReader
{
private:
    static Config config;
    static void readMinSupport(const std::string& line);
    static void readGSP(const std::string& line);
    static void readMinGap(const std::string& line);
    static void readMaxGap(const std::string& line);
    static void readMaxTime(const std::string& line);
    static void readWindow(const std::string& line);
    static void error(const std::string& line);

    std::map<std::string, LineProcessor> _keywordMap;

    ConfigReader();
public:
    static ConfigReader& getInstance();
    void readConfig(InputReader& input);
    Config getConfig();
};


#endif // CONFIGREADER_H
