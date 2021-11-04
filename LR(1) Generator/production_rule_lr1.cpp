#include "production_rule_lr1.h"

ProductionRuleLR1::ProductionRuleLR1(int rule_index,int pointer,int look_aheads_index):
    rule_index(rule_index)
    ,pointer(pointer)
    ,look_aheads_index(look_aheads_index){

}
ProductionRuleLR1::~ProductionRuleLR1(){

}

//anticlimatic that State class has the instance grammar, it should be in Grammar class or a wrapper class
int ProductionLR1::get_right_pointer_symbol(){
    return State::grammar.get_right_symbol_from_ith_rule(pointer,rule_index);
}
bool ProductionLR1::is_there_symbol_at(int pointer_offset){
    return State::grammar.is_there_symbol_at(pointer+pointer_offset,rule_index);
}
int ProductionLR1::get_right_symbol_from_ith_rule(int pointer_offset){
    return State::grammar.get_right_symbol_from_ith_rule(pointer+pointer_offset,rule_index);
}
int ProductionLR1::get_left_symbol(){
    return State::grammar.get_left_symbol_from_ith_rule(rule_index);
}
void ProductionLR1::advance_pointer(){
    assert(State::grammar.is_there_symbol_at(pointer+1));
    pointer++;
}

std::unordered_set<int> & get_look_aheads(){
    return Grammar::look_aheads[rule_index];
}

int ProductionLR1::get_rule_index(){
    return rule_index;
}
int ProductionLR1::get_hash(){
    return State::grammar.get_ith_production_rule(rule_index).get_hash();
}