#include "syntactical_analyzer.h"

SyntacticalAnalyzer::SyntacticalAnalyzer(std::string in_file_name){
    std::ifstream in (in_file_name);
    int n,m,to_st_ind,op_type_int;
    std::pair<int,std::pair<OpType,State*> > to_insert;
    
    in >> n;
    table.resize(n,new State());

    for(int i = 0 ; i < n ; i ++){
        in >> m;
        while(m--){
            in >> to_insert.first >> op_type_int >> to_st_ind;
            to_insert.second.first = static_cast<OpType>(op_type_int);
            to_insert.second.second = table[to_st_ind];
            table[i]->adjacent.insert(to_insert);
        }
    }
}
SyntacticalAnalyzer::~SyntacticalAnalyzer(){

}