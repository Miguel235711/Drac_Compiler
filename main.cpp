#include <vector>
#include <utility>
#include <iostream>

#include "lexical_analyzer.h"

int main(){
    LexicalAnalyzer lexical_analyzer;
    std::vector<std::pair<int,std::string> > tokens;
    lexical_analyzer.get_tokens("./tests/ours/0.drac",tokens);
    for(auto token:tokens){
        std::cout << "token label: " << token.first << " token value: " << token.second << "\n";
    }
    return 0;
}