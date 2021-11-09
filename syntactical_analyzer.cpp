#include "syntactical_analyzer.h"

SyntacticalAnalyzer::SyntacticalAnalyzer(std::string automata_in_file_name,std::string rule_in_file_name){
    automata = new SyntacticalAutomata(automata_in_file_name,rule_in_file_name);
}
SyntacticalAnalyzer::~SyntacticalAnalyzer(){

}

bool SyntacticalAnalyzer::is_correct(std::vector<std::pair<int,std::string> > & tokens){
    //automata->restart();
    std::stack<std::pair<bool,int> > st;
    st.push({true,0});
    for(auto token: tokens){
        //std::cout << "token: " << token.first << "\n";
        while(1){
            if(st.empty())
                return false;
            auto x = st.top();
            std::pair<OpType,int> mov;
            if(x.first){
                ///stack , token
                auto tk = token;
                mov = automata->get_mov(x.second,tk.first); ///hyper DIRTY reference !!!!!!!!!!!!!!!!!!!
                if(tk.first!=token.first){
                    std::cout << "entered hyper dirty reference\n";
                    st.push({false,SyntacticalAutomata::empty_symbol});
                }
            }else{
                ///stack, stack
                st.pop();
                if(st.empty())
                    return false;
                auto y = st.top();
                assert(y.first); /// check that it is a state
                mov = automata->get_mov(y.second,x.second);
                st.push(x);
            }
            if(mov.first == None){
                //syntatical error
                return false;
            }else if(mov.first == Reduction){
                //std::cout << "Reduction! " << st.size() << "\n";
                if(!automata->handle_reduction(st,mov.second))
                    //syntatical error
                    return false;
                if(st.size()==2&&!st.top().first&&st.top().second==-1&&token.first==SyntacticalAutomata::end_symbol) ///only specifict to grammar  with first left non terminal as -1
                    return true;
            }else{
                if(mov.first == Shift){
                    st.push({false,token.first});
                    st.push({true,mov.second});                   
                    break;
                }else{
                    //(mov.first == GoTo){
                    st.push({true,mov.second});
                }
            }
        }
    }
    return false;
}