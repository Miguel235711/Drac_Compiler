#include "state.h"

State::State(State * parent_state){
    st_label=st_label_counter++;
    if(parent_state==NULL){
        //make state 0
        grammar.get_closure_zero();
    }else{
        //make state i (where i > 0) based on parent_state

    }
    //std::cout << "st_label: " << st_label << "\n";
}
State::~State(){

}