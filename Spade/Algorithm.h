#include "Config/Config.h"
#include "Types.h"

#pragma once

class Algorithm {
    Config _config;
public:
    Algorithm(Config &config);
    void run(TransactionList transactions);
};
