#ifndef AUTOMATA_H
#define AUTOMATA_H


#include "production_rule_lr1.h"
#include "grammar.h"
#include "hash_trie.h"
#include "state.h"


#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cwchar>
#include <vector>
#include <algorithm>

//testing libraries

#include <vector>
#include <cassert>

class Automata{
    public:
        Automata(Grammar * grammar,std::string out_file_name);
        virtual ~Automata();
    private:
        int st_label_counter=0;
        std::vector<State*> states;
        HashTrie hash_trie;
        Grammar * grammar;
        std::unordered_set<int> reduced_rules;
        void dfs(State * state);
        std::vector<std::pair<int,int> > get_hashes(std::vector<ProductionRuleLR1*> & productions);
        void print_info(State * state);
};

#endif // AUTOMATA_H