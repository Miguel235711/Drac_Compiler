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
        static Grammar grammar; ///change of place later!!!!
        static std::vector<State *> states; 
        std::vector<ProductionLR1> get_rules();
        void add_next(int symbol, State * state);
        void generate_graph_from_here();
        std::vector<int> get_hashes(std::vector<ProductionLR1> & productions);
        void set_closure_zero();  
    private:
        std::vector<ProductionRuleLR1> rules;
        int st_label;
        std::map<int,State *> next_states;
        enum OpType{Reduction,Shift,GoTo};
        std::map<int,std::pair<int,OpType> > with_to;
        void dfs(State * state);
        std::vector<ProductionRuleLR1> generate_closure(std::vector<int> sub_local_rule_inds);
};

#endif // STATE_H