#ifndef SYNTACTICAL_ANALYZER_H
#define SYNTACTICAL_ANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stack>

#include "syntactical_automata.h"


class SyntacticalAnalyzer {
    public: 
        
        SyntacticalAnalyzer(std::string automata_in_file_name,std::string rule_in_file_name);
        virtual ~SyntacticalAnalyzer();
        bool is_correct(std::vector<std::pair<int,std::string> > & tokens);

    private:

        SyntacticalAutomata * automata;        

};

#endif // SYNTACTICAL_ANALYZER_H