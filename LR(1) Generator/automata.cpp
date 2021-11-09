#include "automata.h"

Automata::Automata(Grammar * grammar,std::string out_file_name):grammar(grammar){
    ///init closure 0
    //std::cout << "closures zero size(): " << grammar->get_closures_zero().size() << "\n";
    //std::cout << "a:\n";
    states.push_back(new State(grammar->get_closures_zero(),st_label_counter));
    auto hashes = get_hashes(states[0]->rules);
    hash_trie.insert_state(hashes,states[0]);
    //std::cout << "b:\n";
    //print_info(states[0]);
    dfs(states[0]);
    std::cout << "state count: " << st_label_counter << "rules reduces: " << reduced_rules.size() << "\n";
    std::cout << "rules not reduced:\n";
    auto rules_number = grammar->get_rule_number();
    for(size_t i = 0 ; i < rules_number; i ++)
        if(reduced_rules.find(i)==reduced_rules.end())
            std::cout << i << " ";
    std::cout << "\n";
    //print to file
    std::ofstream out(out_file_name);
    out << st_label_counter<<"\n";
    for(auto state:states){
        out << state->syntactical_tab_info.size() << "\n";
        for(auto edge: state->syntactical_tab_info){
            out << edge.first << " " << edge.second.first << " " << edge.second.second << "\n";
        }
    }
}

Automata::~Automata(){

}

void Automata::dfs(State * state){
    //std::cout << "label: " << state->label << "\n";
    std::unordered_map<int,std::vector<ProductionRuleLR1*> > productions_rules_of_each_symbol;
    for(auto production_rule : state->rules){
        /*if(state->label==0){
            std::cout << "look_aheads.size(): " << production_rule->get_look_aheads().size() << "\n";
         }*/
        int rule_label = production_rule->get_rule_label();
        /*if(production_rule->get_rule_label()==5){
                std::cout << "weird\n";
            }*/
        if(production_rule->at_symbol()){
            /*if(rule_label==5)
                std::cout << "at symbol: " << production_rule->get_right_pointer_symbol() << "\n";*/
            productions_rules_of_each_symbol[production_rule->get_right_pointer_symbol()].push_back(production_rule);
        }else{
            //std::cout << "Reduction in state " << state->label << "\n";
            //reduction for all look aheads
            //std::cout << "production_rule->get_look_aheads().size(): " << production_rule->get_look_aheads().size() << "\n";
            for(auto symbol : production_rule->get_look_aheads()){
                reduced_rules.insert(rule_label);
                assert(state->syntactical_tab_info.find(symbol)==state->syntactical_tab_info.end()); //conflict
                state->syntactical_tab_info[symbol]={Reduction,rule_label};
            }
        }
    }
    //std::cout << "productions_rules_of_each_symbol\n";
    ///generate edge and point to (new state or already generated state)
    for(auto symbol_and_production_rules : productions_rules_of_each_symbol){
        //std::cout << "symbol: " << symbol_and_production_rules.first << " number of rules: " << symbol_and_production_rules.second.size() << "\n";
        std::vector<ProductionRuleLR1 *> production_rules;
        //Copy production rules and advance their respective pointers
        for(auto production_rule: symbol_and_production_rules.second){
            ///make copy
            auto new_production_rule = new ProductionRuleLR1(*production_rule);
            //std::cout << "vs: " << production_rule->get_look_aheads().size() << " " << new_production_rule->get_look_aheads().size() << "\n";
            //advance pointer
            new_production_rule->advance_pointer();
            production_rules.push_back(new_production_rule);
        }
        //....
        //generate hashes
        //std::cout << "c:\n";
        grammar->get_closures(production_rules);
        //std::cout << "after closure.size(): " << production_rules.size() << " -> ";
        auto hashes = get_hashes(production_rules);
        /*std::cout << "hashes: ";
        for(auto hash: hashes){
            std::cout << hash << " ";
        }
        std::cout << "\n";*/
        //check in Trie if the automata already exists
        State * next_state = hash_trie.get_state(hashes);
        if(next_state == NULL){
            next_state = new State(production_rules,st_label_counter);
            states.push_back(next_state);
            ///add to hash_trie
            hash_trie.insert_state(hashes,next_state);
            //std::cout << "amount of production rules for state " << next_state->label << " is " << production_rules.size() << "\n";
            //if(state->label==0)
            dfs(next_state);
        }
        //add new_state to adjacents
        auto symbol =  symbol_and_production_rules.first;
        state->adjacent[symbol]=next_state;
        //add movement
        assert(state->syntactical_tab_info.find(symbol)==state->syntactical_tab_info.end()); //conflict
        state->syntactical_tab_info[symbol]={symbol < 0 || grammar->get_empty_symbol()==symbol  ? GoTo : Shift,next_state->label}; ///!!!Especial case for empty symbol and end_symbol
    }
   //if(state->label == 1)
    //    symbol == grammar->get_end_symbol() && state->label == 1 ? Acceptance :
    //print_info(state);
}

void Automata::print_info(State * state){
    std::cout << "State " << state->label << "\n" ; 
    //std::cout << " syntactical_tab_info.size(): " << state->syntactical_tab_info.size() << "\n";
    for(auto symbol_and_mov: state->syntactical_tab_info){
        std::cout << symbol_and_mov.first << " -> (" << symbol_and_mov.second.first << " " << symbol_and_mov.second.second << ")\n";
    }
}

std::vector<int> Automata::get_hashes(std::vector<ProductionRuleLR1*> & productions){
    std::vector<int> hashes;
    for(auto production : productions)
        hashes.push_back(production->get_hash());
    ///sort
    std::sort(hashes.begin(),hashes.end());
    return hashes;
}