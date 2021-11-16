#ifndef SYNTACTICAL_ANALYZER_H
#define SYNTACTICAL_ANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stack>
#include <iostream>
#include <cassert>

#include "rules_driver.h"
#include "LR(1) Generator\\op_type.h"



class SyntacticalAnalyzer {
    public: 
        
        SyntacticalAnalyzer(std::string automata_in_file_name,std::string rule_in_file_name);
        virtual ~SyntacticalAnalyzer();
        bool is_correct(std::vector<std::pair<int,std::string> > & tokens);
        static int empty_symbol,end_symbol;

    private:

        struct State{
            std::unordered_map<int,std::pair<OpType,int> > adjacent;
            State(){}
        };

        std::vector<State*> table;
        RulesDriver * rules_driver;     

        std::pair<bool,std::pair<OpType,int> >  get_mov(int state,int symbol);
        bool handle_reduction(std::stack<std::pair<bool,int> > & st,int rule_number);


};

#endif // SYNTACTICAL_ANALYZER_H