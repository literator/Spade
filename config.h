#ifndef CONFIG_H
#define CONFIG_H

#include <limits.h>

/**
 *	Sequence finder configuration
 */
class Config
{
private:
    unsigned int 	_minSupport;		//minimal number of sequence occurrances to mark it as frequent (only sequences that occur more times than this parameter are frequent)
    bool			_useGSP;			//flag whether to find generalized sequences or not
    unsigned int	_minGap;			//GSP only - the minimal time between consecutive transactions in a sequence (default - 0)
    unsigned int	_maxGap;			//GSP only - the maximal time between consecutive transactions in a sequence (default - infinity)
    unsigned int	_maxTime;			//GSP only - the maximal time of sequence (default - infinity)
    unsigned int	_window;			//GSP only - width of a window for combining sequences (deafult - 0)
public:
    Config() : _minSupport(0), _useGSP(false), _minGap(0), _maxGap(UINT_MAX), _maxTime(UINT_MAX), _window(0) {};

    inline unsigned int minSupport() const { return this->_minSupport; };
    void minSupport(const unsigned int value);

    inline bool useGSP() const { return this->_useGSP; };
    inline void useGSP(const bool value) { this->_useGSP = value; };

    inline unsigned int minGap() const { return this->_minGap; };
    void minGap(const unsigned int value);

    inline unsigned int maxGap() const { return this->_maxGap; };
    void maxGap(const unsigned int value);

    inline unsigned int maxTime() const { return this->_maxTime; };
    void maxTime(const unsigned int value);

    inline unsigned int window() const { return this->_window; };
    void window(const unsigned int value);

    void validate() const;
};

#endif // CONFIG_H
