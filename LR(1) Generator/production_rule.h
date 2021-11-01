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
    private:
        int left_non_terminal;
        std::vector<int> right_symbols;
};

#endif // PRODUCTION_RULE_H