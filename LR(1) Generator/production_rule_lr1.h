#ifndef PRODUCTION_RULE_LR1_H
#define PRODUCTION_RULE_LR1_H

#include "production_rule.h"


#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cwchar>
#include <unordered_set>

//testing libraries

#include <vector>
#include <cassert>

class ProductionRuleLR1 : ProductionRule{
    public:
        ProductionRuleLR1(int left_non_terminal);
        virtual ~ProductionRuleLR1();
        
    private:
        std::unordered_set<int> look_aheads;
        int pointer;
};

#endif // PRODUCTION_RULE_LR1_H