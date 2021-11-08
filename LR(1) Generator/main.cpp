#include "grammar.h"
#include "automata.h"

#include <vector>

//Execute Graph Creation

//static variables initialization
int ProductionRule::hash_symbol_count = 89 , ProductionRule::hash_modulo = 1000000123, ProductionRule::min_symbol_value = 44;
Grammar * grammar = new Grammar(/*"drac grammar.txt"*/"test_grammar_0.txt"/*"test_grammar_1.txt"*/,40,41);
Automata automata(grammar);
int main(){
        
    //create automata 
    
    return 0;
}