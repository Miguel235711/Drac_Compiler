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
        void get_closures(std::vector<ProductionRuleLR1> & productions_rules_for_state);
        vector<ProductionRuleLR1> get_closures_zero();
        bool is_there_symbol_at(int pointer,int i);
        int get_right_symbol_from_ith_rule(int pointer,int i);
        int get_left_symbol_from_ith_rule(int i);
        ProductionRule & get_ith_production_rule(int i);
        std::vector<int> get_right_symbols_from_ith_rule(int i);
        static std::vector<std::unordered_set<int> > look_aheads; //global
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
        void dfs_get_closure(int left_symbol,std::unordered_set<int> & visited,std::vector<ProductionRuleLR1> & closure_rules,std::map<int,int> & left_symbol_to_target_look_aheads);
        std::unordered_map<int,left_non_terminal_info> to_left_non_terminal_info;
        int end_symbol,empty_symbol;

};

#endif // GRAMMAR_H