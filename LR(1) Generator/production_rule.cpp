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
int ProductionRule::get_left_non_terminal(){
    return left_non_terminal;
}