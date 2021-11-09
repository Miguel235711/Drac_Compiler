#include "syntactical_automata.h"

SyntacticalAutomata::SyntacticalAutomata(std::string automata_in_file_name,std::string rule_in_file_name){
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
SyntacticalAutomata::~SyntacticalAutomata(){

}

std::pair<OpType,int> SyntacticalAutomata::get_mov(int state,int & symbol){
    auto & adj = table[state]->adjacent;
    //std::cout << adj.size() << "\n";
    auto it = adj.find(symbol);
    //std::cout << "state: " << state << " symbol: " << symbol << " it==adj.end() " << (it==adj.end()) << "\n";
    if(it==adj.end()){
        auto it2 = adj.find(empty_symbol);
        std::cout << (it2==adj.end()) << "\n";
        if(it2==adj.end()){
            return {None,-1};
        }else{
            symbol = empty_symbol;
            return it2->second;
        }
    }else
        return it->second; 
}

bool SyntacticalAutomata::handle_reduction(std::stack<std::pair<bool,int> > & st,int rule_number){
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