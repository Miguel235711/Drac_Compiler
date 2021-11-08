#include "production_rule.h"


ProductionRule::ProductionRule(int rule_label,int left_non_terminal):rule_label(rule_label),left_non_terminal(left_non_terminal){

}

ProductionRule::~ProductionRule(){

}

void ProductionRule::add_right_symbol(int symbol){
    right_symbols.push_back(symbol);
    //std::cout << "right symbols of size " << left_non_terminal << " is " << right_symbols.size() << "\n";
    //std::cout << "\n";   
}

int ProductionRule::get_ith_right_symbol(size_t i){
    assert(is_there_symbol_at(i));
    return right_symbols[i];
}

int ProductionRule::get_left_non_terminal(){
    return left_non_terminal;
}

int ProductionRule::get_hash(){
    int x = normalize_symbol_for_hash(left_non_terminal);
    int p = hash_symbol_count;
    for(auto symbol: right_symbols){
        x += (int64_t) p * normalize_symbol_for_hash(symbol) % hash_modulo;
        x %= hash_modulo;
        p = (int64_t) p * hash_symbol_count % hash_modulo;
    }
    return x;
}
int ProductionRule::normalize_symbol_for_hash(int symbol){
    return symbol + min_symbol_value;
}

int ProductionRule::get_rule_label(){
    return rule_label;
}
bool ProductionRule::is_there_symbol_at(size_t i){
    return i < right_symbols.size();
}