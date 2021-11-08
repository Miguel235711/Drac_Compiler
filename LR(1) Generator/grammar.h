#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "grammar.h"
#include "production_rule.h"
#include "production_rule_lr1.h"


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
        Grammar(const std::string grammar_specification_input_file_name,int end_symbol,int empty_symbol);
        virtual ~Grammar();
        void get_closures(std::vector<ProductionRuleLR1*> & productions_rules_for_state);
        std::vector<ProductionRuleLR1*> get_closures_zero();
    private:

        struct left_non_terminal_info{
            std::unordered_set<int> children,firsts;
            std::vector<ProductionRule*> rules;
            left_non_terminal_info(){}
        };

        std::vector<ProductionRule *> rules; ///Ch!
        std::string input_file_name /*= "drac grammar.txt"*/ /*"test_grammar_0.txt"*/;
        std::unordered_map<int,left_non_terminal_info> to_left_non_terminal_info;
        int end_symbol,empty_symbol,rule_count = 0;

        void calc_firsts();
        void load_rules();
        void get_reachable(int left_symbol,std::unordered_set<int> & visited);
        void update_look_aheads(ProductionRuleLR1 * rule,std::unordered_map<int,std::unordered_set<int> > & non_terminal_to_look_aheads);
        void dfs_get_closure(int left_symbol,std::unordered_set<int> & visited,std::vector<ProductionRuleLR1*> & closure_rules,std::unordered_map<int,std::unordered_set<int> > & non_terminal_to_look_aheads);
};

#endif // GRAMMAR_H