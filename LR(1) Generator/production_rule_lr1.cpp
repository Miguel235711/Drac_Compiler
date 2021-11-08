#include "production_rule_lr1.h"

ProductionRuleLR1::ProductionRuleLR1(ProductionRule * base_rule):ProductionRule(*base_rule){
    //std::cout << "right_symbols.size(): " << right_symbols.size() << "\n";
    /*for(auto right_symbol: right_symbols){
        std::cout << right_symbol << " ";
    }*/
    //std::cout << "\n";
}
ProductionRuleLR1::~ProductionRuleLR1(){

}

int ProductionRuleLR1::get_right_pointer_symbol(){
    //std::cout << "symbol count: " << right_symbols.size() << "\n";
    assert(at_symbol());
    return right_symbols[pointer];
}
void ProductionRuleLR1::advance_pointer(){
    pointer++;
}

std::unordered_set<int> & ProductionRuleLR1::get_look_aheads(){
    return look_aheads;
}

bool ProductionRuleLR1::at_symbol(){
    return pointer < right_symbols.size();
}
int ProductionRuleLR1::get_hash(){
   int hash = ProductionRule::get_hash();
   int p = my_pow(hash_symbol_count,right_symbols.size()+1);
   for(auto symbol: look_aheads){
        hash += (int64_t) p * normalize_symbol_for_hash(symbol) % hash_modulo;
        hash %= hash_modulo;
        p = (int64_t) p * hash_symbol_count % hash_modulo;
    }
    return hash;
}
int ProductionRuleLR1::my_pow(int b,int e){
    if(!e)
        return 1;
    int x = my_pow(b,e>>1);
    return  (int64_t) ( (int64_t) x * x % hash_modulo ) * (e&1 ? b : 1) % hash_modulo;
}

void ProductionRuleLR1::set_look_aheads(std::unordered_set<int> look_aheads){
    this->look_aheads=look_aheads;
}

int ProductionRuleLR1::get_ith_right_symbol_offset(size_t offset){
    return get_ith_right_symbol(pointer+offset);
}
bool ProductionRuleLR1::is_there_symbol_at_offset(size_t offset){
    //std::cout << "left_symbol: " << get_left_non_terminal() << "pointer: " << pointer << " offset: " << offset << "\n";
    return is_there_symbol_at(pointer+offset);
}