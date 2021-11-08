#ifndef PRODUCTION_RULE_H
#define PRODUCTION_RULE_H

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

class ProductionRule{
    public:
        
        ProductionRule(int rule_label,int left_non_terminal);
        virtual ~ProductionRule();
        void add_right_symbol(int symbol);
        int get_left_non_terminal();
        int get_ith_right_symbol(size_t i);
        int get_hash();
        int get_rule_label();
        bool is_there_symbol_at(size_t i);
        
        static int hash_symbol_count,hash_modulo,min_symbol_value;
    private:
        int rule_label,left_non_terminal;
        
    protected:
        int normalize_symbol_for_hash(int symbol);
        std::vector<int> right_symbols;
};

#endif // PRODUCTION_RULE_H