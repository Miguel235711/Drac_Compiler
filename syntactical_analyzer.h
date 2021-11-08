#ifndef SYNTACTICAL_ANALYZER_H
#define SYNTACTICAL_ANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "LR(1) Generator\\op_type.h"

class SyntacticalAnalyzer {
    public: 
        
        SyntacticalAnalyzer(std::string in_file_name);
        virtual ~SyntacticalAnalyzer();
    
    private:

        struct State{
            std::unordered_map<int,std::pair<OpType,State*> > adjacent;
            State(){}
        };

        std::vector<State*> table;

};

#endif // SYNTACTICAL_ANALYZER_H