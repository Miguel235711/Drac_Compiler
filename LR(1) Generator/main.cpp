#include "state.h"
#include "grammar.h"


//Execute Graph Creation

//static variables initialization
int State::st_label_counter = 0, ProductionRule::hash_symbol_count = 89 , ProductionRule::hash_modulo = 1000000123, ProductionRule::min_symbol_value = 44;
Grammar State::grammar("drac grammar.txt",40,41);
std::vector<std::unordered_set<int> > Grammar::look_aheads;
std::vector<State *> State::states; //think how to manage this because it is going to be also managed by a Trie 
int main(){
        
    //create states
    auto & states = State::states;
    states.push_back(new State()); 
    auto * root = states.back();
    root->set_closure_zero();
    root->generate_from_here();
    return 0;
}