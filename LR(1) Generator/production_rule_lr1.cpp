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

std::set<int> & ProductionRuleLR1::get_look_aheads(){
    return look_aheads;
}

bool ProductionRuleLR1::at_symbol(){
    return pointer < right_symbols.size();
}
std::pair<int,int> ProductionRuleLR1::get_hash(){
    int initial = normalize_symbol_for_hash(left_non_terminal);
    std::pair<int,int> hash = {initial,initial};
    std::pair<int,int> p = {hash_symbol_count,hash_symbol_count};
    int  i = 0 ;
    for(auto symbol: right_symbols){
        handle_update_hash_for_pointer(hash,p,i);
        update_hash(hash,symbol,p);
        i ++;
    }
    handle_update_hash_for_pointer(hash,p,i);
    update_hash(hash,max_symbol_value+2,p);
    for(auto symbol: look_aheads){
        update_hash(hash,symbol,p);
    }
    //std::cout << "hash: " << hash << "\n";
    return hash;
}

void ProductionRuleLR1::update_hash(std::pair<int,int> & hash,int symbol,std::pair<int,int> & p){
    hash.first += (int64_t) p.first * normalize_symbol_for_hash(symbol) % hash_modulo_1;
    hash.first %= hash_modulo_1;
    hash.second += (int64_t) p.second * normalize_symbol_for_hash(symbol) % hash_modulo_2;
    hash.second %= hash_modulo_2;
    p = get_next_p(p);
}
void ProductionRuleLR1::handle_update_hash_for_pointer(std::pair<int,int> & hash,std::pair<int,int> & p,int i){
    if(i==pointer){
        update_hash(hash,max_symbol_value+1,p);
        p = get_next_p(p);
    }
}

std::pair<int,int> ProductionRuleLR1::get_next_p(std::pair<int,int> p){
    return {(int64_t) p.first * hash_symbol_count % hash_modulo_1,(int64_t) p.second * hash_symbol_count % hash_modulo_2}; 
}
/*int ProductionRuleLR1::my_pow(int b,int e){
    if(!e)
        return 1;
    int x = my_pow(b,e>>1);
    return ( (int64_t) x * x % hash_modulo ) * (e&1 ? b : 1) % hash_modulo;
}*/

void ProductionRuleLR1::set_look_aheads(std::set<int> look_aheads){
    this->look_aheads=look_aheads;
}

int ProductionRuleLR1::get_ith_right_symbol_offset(size_t offset){
    return get_ith_right_symbol(pointer+offset);
}
bool ProductionRuleLR1::is_there_symbol_at_offset(size_t offset){
    //std::cout << "left_symbol: " << get_left_non_terminal() << "pointer: " << pointer << " offset: " << offset << "\n";
    return is_there_symbol_at(pointer+offset);
}