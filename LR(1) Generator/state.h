#ifndef STATE_H 
#define STATE_H 

#include <unordered_map>
#include <vector>

#include "production_rule_lr1.h"
#include "op_type.h"


struct State{
    int label;
    std::unordered_map<int,State *> adjacent;
    std::vector<ProductionRuleLR1*> rules;
    std::unordered_map<int,std::pair<OpType,int> > syntactical_tab_info; //<symbol,<op_type,state_label or rule_index>>
    State(std::vector<ProductionRuleLR1*>rules,int & st_label_counter):rules(rules){
        label = st_label_counter++;
    }
};

#endif // STATE_H