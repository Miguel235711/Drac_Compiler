#include "syntactical_analyzer.h"

SyntacticalAnalyzer::SyntacticalAnalyzer(std::string automata_in_file_name,std::string rule_in_file_name){
    std::ifstream in (automata_in_file_name);
    int n,m,to_st_ind,op_type_int;
    std::pair<int,std::pair<OpType,int> > to_insert;
    
    in >> n;
    table.resize(n);
    //std::cout << "n: " << n << "\n";
    for(int i = 0 ; i < n ; i ++){
        table[i] = new State();
        in >> m;
        /*if(i==0)
            std::cout << "m: " << m << "\n";*/
        while(m--){
            in >> to_insert.first >> op_type_int >> to_insert.second.second;
            /*if(i==0)
                std::cout << "symbol: " << to_insert.first << "\n";*/
            to_insert.second.first = static_cast<OpType>(op_type_int);
            table[i]->adjacent.insert(to_insert);
        }
    }


    rules_driver = new RulesDriver(rule_in_file_name);
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
            ///begin print stack
            auto st_d = st;
            std::cout << "stack:\n";
            while(!st_d.empty())
                std::cout << st_d.top().first << " " << st_d.top().second << " | ",st_d.pop();
            std::cout<<"\n";
            //end
            if(st.empty())
                return false;
            auto x = st.top();
            std::pair<bool,std::pair<OpType,int> > mov;
            if(x.first){
                ///stack , token
                mov = get_mov(x.second,token.first);
            }else{
                ///stack, stack
                st.pop();
                if(st.empty())
                    return false;
                auto y = st.top();
                assert(y.first); /// check that it is a state
                mov = get_mov(y.second,x.second);
                st.push(x);
            }
            ///special weird case
            if(mov.first){
                std::cout << "added empty to stack\n";
                st.push({false,empty_symbol});
            }
            if(mov.second.first == None){
                //syntatical error
                return false;
            }else if(mov.second.first == Reduction){
                //std::cout << "Reduction! " << st.size() << "\n";
                if(!handle_reduction(st,mov.second.second))
                    //syntatical error
                    return false;
                if(st.size()==2&&!st.top().first&&st.top().second==-1&&token.first==end_symbol) ///only specifict to grammar  with first left non terminal as -1
                    return true;
            }else{
                if(mov.second.first == Shift){
                    st.push({false,token.first});
                    st.push({true,mov.second.second});                   
                    break;
                }else{
                    //(mov.first == GoTo){
                    st.push({true,mov.second.second});
                }
            }
        }
    }
    return false;
}
std::pair<bool,std::pair<OpType,int> > SyntacticalAnalyzer::get_mov(int state,int symbol){
    auto & adj = table[state]->adjacent;
    //std::cout << adj.size() << "\n";
    auto it = adj.find(symbol);
    //std::cout << "state: " << state << " symbol: " << symbol << " it==adj.end() " << (it==adj.end()) << "\n";
    if(it==adj.end()){
        auto it2 = adj.find(empty_symbol);
        std::cout << (it2==adj.end()) << "\n";
        if(it2==adj.end()){
            return {false,{None,-1}};
        }else{
            //symbol = empty_symbol;
            return {true,it2->second};
        }
    }else
        return {false,it->second}; 
}
bool SyntacticalAnalyzer::handle_reduction(std::stack<std::pair<bool,int> > & st,int rule_number){
    auto rule = rules_driver->get_rule(rule_number);
    //std::cout << "rule_number: " << rule_number << "\n";
    for(int i = -1 ;rule->is_there_symbol_at(i);i--){
        auto r_symbol = rule->get_ith_right_symbol(i);
        /*if(r_symbol==empty_symbol&&!st.empty()){ ///especial case because we know that empty means only this symbol DANGEROUS!!!!!!!!!!
            ///pop state
            std::cout << "especial\n";
            st.pop();
            break;
        }*/
        //std::cout << "r_symbol: " << r_symbol << "i: " << i << "\n";
        if(!st.empty()&&st.top().first){
            i++;
        }else{
            if(st.empty() || r_symbol!=st.top().second)
                //could not reduce
                return false; 
        }
        st.pop();
    }
    //std::cout << "rule_number: " << rule_number << "\n";
    st.push({false,rule->get_left_non_terminal()});
    return true;
}
