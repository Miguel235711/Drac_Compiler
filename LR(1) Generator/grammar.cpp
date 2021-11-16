#include "grammar.h"


Grammar::Grammar(const std::string grammar_specification_input_file_name,int end_symbol,int empty_symbol):
    end_symbol(end_symbol)
    ,empty_symbol(empty_symbol){
        load_rules(grammar_specification_input_file_name);
        calc_firsts();
}

Grammar::~Grammar(){

}

void Grammar::calc_firsts(){
     ///MOdifiy
    //TODO
    ///calculate children and direct firsts
    for(auto rule : rules){
        int left_non_terminal = rule->get_left_non_terminal();
        auto & info = to_left_non_terminal_info[left_non_terminal];
        info.rules.push_back(rule);
        if(rule->is_there_symbol_at(0)){
            int first_right_symbol = rule->get_ith_right_symbol(0) ;
            //std::cout << "rule " << i << " first_right_symbol: " << first_right_symbol << " left_non_terminal: " << left_non_terminal << "\n";
            //auto info_it = to_left_non_terminal_info.find(left_non_terminal);
            //if(info_it == to_left_non_terminal_info.end())
            //    info_it = to_left_non_terminal_info.insert({left_non_terminal,left_non_terminal_info()}).first;
            auto & which_set = first_right_symbol < 0 ? info.children : info.firsts;
            which_set.insert(first_right_symbol);
        }
    }
    //std::cout << "completed\n";
    //DO one DFS per number to calculate reachable -> O(n^3) try to optimize later
    for(auto & left_symbol_info: to_left_non_terminal_info){
        auto left_symbol = left_symbol_info.first;
        std::unordered_set<int> visited;
        visited.insert(left_symbol);
        get_reachable(left_symbol,visited);
        //add firsts of visited to current left_symbol
        auto & firsts = left_symbol_info.second.firsts;
        for(auto & reachable: visited){
            auto & firsts_reachable = to_left_non_terminal_info[reachable].firsts;
            firsts.insert(firsts_reachable.begin(),firsts_reachable.end());
        }
        //print firsts for debugging
        std::cout << "firsts of " << left_symbol << "\n";
        for(auto first : firsts)
            std::cout << first << " ";
        std::cout << "\n";
    }
}
void Grammar::get_reachable(int left_symbol,std::unordered_set<int> & visited){
    for(const auto & child: to_left_non_terminal_info[left_symbol].children)
        if(visited.find(child)==visited.end()){
            visited.insert(child);
            get_reachable(child,visited);
        }
}
void Grammar::load_rules(std::string in_file_name){
    ///call static method of rule_loader
    rules = RuleLoader::load_rules(in_file_name);
}

void Grammar::dfs_get_closure(int left_symbol,std::unordered_set<int> & visited,std::vector<ProductionRuleLR1*> & closure_rules,std::unordered_map<int,std::set<int> > & non_terminal_to_look_aheads){
    ///check if visited
    if(visited.find(left_symbol)!=visited.end())
        return;
    visited.insert(left_symbol);
    ///add rules belonging to this symbol
    auto & to_left_non_terminal_info_things = to_left_non_terminal_info[left_symbol];
    for(auto rule : to_left_non_terminal_info_things.rules){
        //std::cout << "left symbol: " << left_symbol << "\n";
        ProductionRuleLR1 * rule_lr1 =  new ProductionRuleLR1(rule);
        rule_lr1->set_look_aheads(non_terminal_to_look_aheads[left_symbol]);
        if(rule_lr1->at_symbol()&&rule_lr1->get_right_pointer_symbol()<0)
            update_look_aheads(rule_lr1,non_terminal_to_look_aheads);
        //if(rule_lr1->get_rule_label()==5)
         //   std::cout << "5 got\n";
        closure_rules.push_back(rule_lr1);
    }
    for(auto child_left_symbol: to_left_non_terminal_info_things.children)
        dfs_get_closure(child_left_symbol,visited,closure_rules,non_terminal_to_look_aheads);
}

void Grammar::get_closures(std::vector<ProductionRuleLR1*> & productions_rules_for_state){ ///FIX
    //precalculate look_aheads for right_pointer_symbol
    std::unordered_map<int,std::set<int> > non_terminal_to_look_aheads;
    //std::cout << "rules for closure: " << productions_rules_for_state.size() << "\n";
    for(auto production_rule_for_state: productions_rules_for_state){
        //std::cout << "get_closures::rule: " << production_rule_for_state->get_rule_label() << "\n";
        ///add previously calculated look_aheads
        int left = production_rule_for_state->get_left_non_terminal();
        auto & look_adheads_of_left = production_rule_for_state->get_look_aheads();
        non_terminal_to_look_aheads[left].insert(look_adheads_of_left.begin(),look_adheads_of_left.end());
        //add look_aheads of right symbol
        if(production_rule_for_state->at_symbol()){
            int right_symbol_to_get_look_aheads = production_rule_for_state->get_right_pointer_symbol();
            //std::cout << "right_symbol_to_get_look_aheads: " << right_symbol_to_get_look_aheads << "\n";
            if(right_symbol_to_get_look_aheads<0){
                //std::cout << "**** rule_label: " << production_rule_for_state->get_rule_label() << "right: " << right_symbol_to_get_look_aheads << "\n";
                update_look_aheads(production_rule_for_state,non_terminal_to_look_aheads);
            }
        }
    }
    //add all mapped look_aheads to look_aheads vector and create data structure for dfs_get_closure
    // std::map<int,int> left_symbol_to_target_look_aheads;
    // for(auto & non_terminal_to_look_aheads_item: non_terminal_to_look_aheads){
    //     left_symbol_to_target_look_aheads[non_terminal_to_look_aheads_item.first]=look_aheads.size()-1;
    // }
    ///TODO
    ///for each base productions_rules_for_state
    std::unordered_set<int> visited;
    int sz = productions_rules_for_state.size();
    for(int i = 0 ; i < sz ; i ++){
        if(productions_rules_for_state[i]->at_symbol()&&productions_rules_for_state[i]->get_right_pointer_symbol()<0)
            dfs_get_closure(productions_rules_for_state[i]->get_right_pointer_symbol(),visited,productions_rules_for_state,non_terminal_to_look_aheads);
    }
}

void Grammar::update_look_aheads(ProductionRuleLR1 * rule,std::unordered_map<int,std::set<int> > & non_terminal_to_look_aheads){
    auto right_symbol_to_get_look_aheads  = rule->get_right_pointer_symbol();
    auto & look_aheads = non_terminal_to_look_aheads[right_symbol_to_get_look_aheads];
    //TODO!!!!
    //add corresponding nexts to look_aheads
    bool is_there_empty_first = true;
    for(int i = 1 ; is_there_empty_first && rule->is_there_symbol_at_offset(i) ; i ++){
        //std::cout << "rule_label: " << rule->get_rule_label() << " entered update for lookadheads\n";
        is_there_empty_first = false;
        auto symbol = rule->get_ith_right_symbol_offset(i);
        if(symbol<0){
            //add firsts. Remove empty symbol if present and mark is_there_empty_first flag
            auto & firsts = to_left_non_terminal_info[symbol].firsts;
            look_aheads.insert(firsts.begin(),firsts.end());
            auto it = look_aheads.find(empty_symbol);
            if(it!=look_aheads.end()){
                is_there_empty_first = true;
                look_aheads.erase(it);
            }
        }else
            look_aheads.insert(symbol);
    }
    if(is_there_empty_first){
        //std::cout << "------rule.label: " << rule->get_rule_label() << "left_non_terminal: " << rule->get_left_non_terminal() << "\n";
        ///consider look aheads of left non-terminal
        auto & left_symbol_look_aheads = non_terminal_to_look_aheads[rule->get_left_non_terminal()];
        //std::cout << "look_aheads.size(): " << look_aheads.size() << "\n";
        //assert(!left_symbol_look_aheads.empty());
        look_aheads.insert(left_symbol_look_aheads.begin(),left_symbol_look_aheads.end());
    }
}

std::vector<ProductionRuleLR1*> Grammar::get_closures_zero(){
    ProductionRuleLR1 * first_rule = new ProductionRuleLR1(rules[0]);
    first_rule->set_look_aheads({end_symbol});
    //std::cout << "look_aheads.size(): " << first_rule->get_look_aheads().size() << "\n";
    std::vector<ProductionRuleLR1*> closure_zero = {first_rule};
    get_closures(closure_zero);
    return closure_zero;
}

int Grammar::get_empty_symbol(){
    return empty_symbol;
}
int Grammar::get_end_symbol(){
    return end_symbol;
}
size_t Grammar::get_rule_number(){
    return rules.size();
}