#include "hash_trie.h"

HashTrie::HashTrie(){

}

HashTrie::~HashTrie(){

}

State * HashTrie::get_state(std::vector<std::pair<int,int> > & seq){
    auto node = root;
    for(auto x:seq){
        auto & adjacent = node->adjacent;
        auto it = adjacent.find(x);
        if(it==adjacent.end()){
            return NULL;
        }
        node = it->second;
    }
    //std::cout << "not null? " <<  (node->state!=NULL);
    return node->state;
}
void HashTrie::insert_state(std::vector<std::pair<int,int> > & seq,State * state){
    auto node = root;
    for(auto x:seq){
        auto & adjacent = node->adjacent;
        auto it = adjacent.find(x);
        if(it==adjacent.end())
            it = adjacent.insert({x,new Node()}).first;
        node = it->second;
    }
    /*std::cout << "seq: ";
    for(auto x: seq)
        std::cout << x << " ";
    std::cout << "\n";
    std::cout << (state == NULL) << "\n";*/
    node->state = state;
}