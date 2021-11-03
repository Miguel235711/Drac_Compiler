#include "production_rule_lr1.h"

ProductionRuleLR1::ProductionRuleLR1(int rule_index,int pointer,std::unordered_set<int> & look_aheads):
    rule_index(rule_index)
    ,pointer(pointer)
    ,look_aheads(look_aheads){

}
ProductionRuleLR1::~ProductionRuleLR1(){

}
int ProductionLR1::get_right_pointer_symbol(){
    State::grammar.get_right_symbol_from_ith_rule(pointer,rule_index);
}