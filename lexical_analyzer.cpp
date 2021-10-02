#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(){

}
LexicalAnalyzer::~LexicalAnalyzer(){

}
bool LexicalAnalyzer::handle_char(char c,std::vector<std::pair<int,std::string> > & tokens,std::string & token,std::ifstream & in){
    if(automata.next(c))
        token.push_back(c);
    else{
        if(automata.in_token()){
            //token found
            int label = automata.get_token_label();
            if(label)
                tokens.push_back({label,token});
            automata.restart();
        }else{
            automata.restart();
            return false; // error
        }
        in.unget();
        token="";
    }
    return true;
}
bool LexicalAnalyzer::get_tokens(const std::string & in_file_name,std::vector<std::pair<int,std::string> > & tokens){
    std::ifstream in(in_file_name);
    char c;
    tokens.clear();
    std::string token;
    while(in.get(c)){
        //std::cout << "c: " << c << "\n";
        if(!handle_char(c,tokens,token,in))
            return false;
    }
    //for last token
    if(!handle_char('\n',tokens,token,in))
        return false;
    return true;
}
