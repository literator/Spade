#include "config.h"

#include <string>

using namespace std;

/**
 *	Min. support setter; value must be larger than 0
 */
void Config::minSupport(const unsigned int value){
    if (value == 0){
        throw string("Minimal support cannot be 0.");
    }
    this->_minSupport = value;
}

/**
 *	Min. gap setter; GSP required
 */
void Config::minGap(const unsigned int value) {
    if (this->_useGSP == false){
        throw string("Setting minimum gap requires GSP.");
    }
    this->_minGap = value;
};

/**
 *	Max pair setter; GSP required
 */
void Config::maxGap(const unsigned int value) {
    if (this->_useGSP == false){
        throw string("Setting maximum gap requires GSP.");
    }
    this->_maxGap = value;
};

/**
 *	Max pair setter; GSP required
 */
void Config::maxTime(const unsigned int value) {
    if (this->_useGSP == false){
        throw string("Setting maximum sequence time requires GSP.");
    }
    this->_maxTime = value;
};

/**
 *	Window setter; GSP required
 */
void Config::window(const unsigned int value) {
    if (this->_useGSP == false){
        throw string("Setting window length requires GSP.");
    }
    this->_window = value;
};


/**
 *	Final validation of seqeunce finder configuration
 */
void Config::validate() const {
    if (_minSupport == 0){
        throw string("Minimal support not set.");
    }
    if (_useGSP && _minGap > _maxGap){
        throw string("Minimal gap cannot be bigger than the maximum gap.");
    }
}
