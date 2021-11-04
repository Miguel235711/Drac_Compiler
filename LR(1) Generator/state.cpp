#include "state.h"

State::State(){
    st_label=st_label_counter++;
    ///add signature to static variable
    //std::cout << "st_label: " << st_label << "\n";
}
void State::add_next(int symbol, State * state){ ///DANGEROUS if not properly used
    next_states[symbol]=state;
}
void State::set_closure_zero(){
    rules = grammar.get_closures_zero();
}
void State::dfs(State * state){
    std::map<int,std::vector<int> > right_target_symbol_to_rule_local_inds;
    int sz = rule.size();
    for(int i = 0 ; i < sz; i ++){
        auto & rule = rules[i];
        int r_symbol = rule.get_right_pointer_symbol(); ///TODO
        auto & indexes =  right_target_symbol_to_rule_local_inds[r_symbol];
        indexes.push_back(i);
    }
    ///generate children or use precalculated
    for(auto & indexes_of_right_target_symbol: right_target_symbol_to_rule_local_inds){
        //makes moves and generate closures
        //....
        //generate hashes
        std::vector<int> hashes = get_hashes(generate_closure(indexes_of_right_target_symbol.second));
        //check in Trie if the state already exists
    }
}
std::vector<ProductionRuleLR1> State::generate_closure(std::vector<int> sub_local_rule_inds){
    std::vector<ProductionRuleLR1> closured_rules;
    for(auto ind : sub_local_rule_inds)
        closured_rules.push_back(rules[ind]);
    grammar.get_closures(closured_rules);
    return closured_rules;
}
void State::generate_graph_from_here(){
    dfs(this);
}
State::~State(){

}
std::vector<ProductionLR1> State::get_rules(){
    return rules;
}

std::vector<int> State::get_hashes(std::vector<ProductionLR1> & productions){
    std::vector<int> hashes;
    for(auto & production : productions)
        hashes.push_back(production.get_hash());
    return hashes;
}