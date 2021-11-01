#ifndef STATE_H
#define STATE_H

#include "state.h"
#include "production_rule_lr1.h"
#include "grammar.h"


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

class State{
    public:
        State();
        virtual ~State();
        static int st_label_counter;
        static Grammar grammar;
    private:
        std::vector<ProductionRuleLR1> rules;
        int st_label;
};

#endif // STATE_H