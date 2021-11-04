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
        ProductionRule(int left_non_terminal);
        virtual ~ProductionRule();
        void add_right_symbol(int symbol);
        int get_first_right_symbol();
        int get_left_non_terminal();
        int get_ith_right_symbol(int i);
        int get_hash();
        static int hash_symbol_count,hash_modulo,min_symbol_value;
    private:
        int left_non_terminal;
        std::vector<int> right_symbols;
        int normalize_symbol_for_hash(int symbol);
};

#endif // PRODUCTION_RULE_H