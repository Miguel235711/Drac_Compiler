#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cwchar>

//testing libraries

#include <vector>
#include <cassert>

#include "lexical_automata.h"

class LexicalAnalyzer{
    public:
        LexicalAnalyzer();
        virtual ~LexicalAnalyzer();
        bool get_tokens(const std::string & in_file_name,std::vector<std::pair<int,std::string> > & tokens);
    private:
        LexicalAutomata automata;
        bool handle_char(char c,std::vector<std::pair<int,std::string> > & tokens,std::string & token,std::ifstream & in);
};

#endif // LEXICAL_ANALYZER_H