#include "state.h"
#include "grammar.h"


//static variables initialization
int State::st_label_counter = 0 ; // exclusive
Grammar State::grammar("drac grammar.txt");

int main(){
    
    //create states
    State * root = new State(NULL);
    
    return 0;
}