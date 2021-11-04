#include "production_rule.h"

ProductionRule::ProductionRule(int left_non_terminal):left_non_terminal(left_non_terminal){

}
ProductionRule::~ProductionRule(){

}
void ProductionRule::add_right_symbol(int symbol){
    right_symbols.push_back(symbol);
    //std::cout << "right symbols of size " << left_non_terminal << " is " << right_symbols.size() << "\n";
    //std::cout << "\n";   
}
int ProductionRule::get_first_right_symbol(){
    assert(!right_symbols.empty());
    return right_symbols[0];
}
int ProductionRule::get_ith_right_symbol(int i){
    assert(i < right_symbols.size());
    return right_symbols[i];
}
int ProductionRule::get_left_non_terminal(){
    return left_non_terminal;
}
int ProductionRule::get_hash(){
    int x = normalize_symbol_for_hash(left_non_terminal);
    int p = hash_symbol_count;
    for(auto symbol: right_symbols){
        x += p * normalize_symbol_for_hash(symbol);
        p = ((int64_t)p * hash_symbol_count)%hash_modulo;
    }
    return x;
}
int ProductionLR1::normalize_symbol_for_hash(int symbol){
    return symbol + min_symbol_value;
}