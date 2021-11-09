#ifndef SYNTACTICAL_AUTOMATA_H
#define SYNTACTICAL_AUTOMATA_H

#include<unordered_map>
#include<vector>
#include<fstream>
#include<string>
#include<stack>

#include "LR(1) Generator\\op_type.h"
#include "rules_driver.h"


///Change class name because is misleading

class SyntacticalAutomata{
    public:
        
        SyntacticalAutomata(std::string automata_in_file_name,std::string rule_in_file_name);
        virtual ~SyntacticalAutomata();

        std::pair<OpType,int> get_mov(int state,int & symbol);
        bool handle_reduction(std::stack<std::pair<bool,int> > & st,int rule_number);

        static int end_symbol,empty_symbol;

    private:

        struct State{
            std::unordered_map<int,std::pair<OpType,int> > adjacent;
            State(){}
        };

        std::vector<State*> table;
        RulesDriver * rules_driver;
};

#endif // SYNTACTICAL_AUTOMATA_H