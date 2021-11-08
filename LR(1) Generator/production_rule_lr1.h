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

#include "production_rule.h"

class ProductionRuleLR1 : public ProductionRule {
    public:

        ProductionRuleLR1(ProductionRule * base_rule);
        virtual ~ProductionRuleLR1();
        int get_right_pointer_symbol();
        void advance_pointer();
        int get_hash();
        bool at_symbol();
        int get_ith_right_symbol_offset(size_t offset);
        bool is_there_symbol_at_offset(size_t offset);
        std::unordered_set<int> & get_look_aheads();
        void set_look_aheads(std::unordered_set<int> look_aheads);
    private:

        std::unordered_set<int> look_aheads;
        size_t pointer=0;
        int my_pow(int b,int e);
};

#endif // PRODUCTION_RULE_LR1_H