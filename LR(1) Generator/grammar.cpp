#include "grammar.h"

Grammar::Grammar(const std::string grammar_specification_input_file_name){
    input_file_name = grammar_specification_input_file_name;
    load_rules();
    calc_firsts();
}
Grammar::~Grammar(){

}

void Grammar::calc_firsts(){
    //TODO
    ///calculate children and direct firsts
    int i = 0;
    for(auto & rule : rules){
        int first_right_symbol = rule.get_first_right_symbol(), left_non_terminal = rule.get_left_non_terminal();
        //std::cout << "rule " << i << " first_right_symbol: " << first_right_symbol << " left_non_terminal: " << left_non_terminal << "\n";
        auto info_it = to_left_non_terminal_info.find(left_non_terminal);
        if(info_it == to_left_non_terminal_info.end())
            info_it = to_left_non_terminal_info.insert({left_non_terminal,left_non_terminal_info()}).first;
        auto & info = info_it->second;
        auto & which_set = first_right_symbol < 0 ? info.children : info.firsts;
        info.to_rule_index.push_back(i);
        which_set.insert(first_right_symbol);
        i++;
    }
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
        /*std::cout << "firsts of " << left_symbol << "\n";
        for(auto first : firsts)
            std::cout << first << " ";
        std::cout << "\n";*/
    }
}
void Grammar::get_reachable(int left_symbol,std::unordered_set<int> & visited){
    for(const auto & child: to_left_non_terminal_info[left_symbol].children)
        if(visited.find(child)==visited.end()){
            visited.insert(child);
            get_reachable(child,visited);
        }
}
void Grammar::load_rules(){
    std::ifstream in(input_file_name.c_str());
    std::string line;
    int symbol;
    while(getline(in,line)){
        //std::cout << "line: " << line << "\n";
        std::stringstream line_stream(line);
        line_stream >> symbol;
        //std:: cout << "left non-terminal: " << symbol << "\n";
        ProductionRule rule(symbol);
        while(line_stream >> symbol){
            //std::cout << "right symbol: " << symbol << "\n";
            rule.add_right_symbol(symbol);
        }
        //std::cout << "what: " << rule.get_first_right_symbol() << "\n";
        rules.push_back(rule);
    }
}