#ifndef PRODUCTION_RULE_LR1_H
#define PRODUCTION_RULE_LR1_H


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

class ProductionRuleLR1{
    public:
        ProductionRuleLR1(int rule_index,int pointer,std::unordered_set<int> & look_aheads);
        virtual ~ProductionRuleLR1();
        int get_right_pointer_symbol();
    private:
        std::unordered_set<int> look_aheads;
        int pointer, rule_index;
};

#endif // PRODUCTION_RULE_LR1_H