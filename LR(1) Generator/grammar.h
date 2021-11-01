#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "grammar.h"
#include "production_rule.h"


#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cwchar>
#include <vector>

//testing libraries

#include <vector>
#include <cassert>

class Grammar{
    public:
        Grammar(const std::string grammar_specification_input_file_name);
        virtual ~Grammar();
        
    private:
        std::vector<ProductionRule> rules;
        std::string input_file_name /*= "drac grammar.txt"*/ /*"test_grammar_0.txt"*/;
        void calc_firsts();
        void load_rules();
        struct left_non_terminal_info{
            std::unordered_set<int> children,firsts;
            std::vector<int> to_rule_index;
            left_non_terminal_info(){}
        };
        void get_reachable(int left_symbol,std::unordered_set<int> & visited);
        std::unordered_map<int,left_non_terminal_info> to_left_non_terminal_info;
};

#endif // GRAMMAR_H