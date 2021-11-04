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
        ProductionRuleLR1(int rule_index,int pointer,int look_aheads_index);
        virtual ~ProductionRuleLR1();
        int get_right_pointer_symbol();
        int get_right_symbol_from_ith_rule(int pointer_offset);
        int get_left_symbol();
        int get_rule_index();
        int get_hash();
        bool is_there_symbol_at(int pointer_offset);
        void advance_pointer();
        std::unordered_set<int> & get_look_aheads();
    private:
        int look_aheads_index;
        int pointer, rule_index;
};

#endif // PRODUCTION_RULE_LR1_H