#ifndef HASH_TRIE_H
#define HASH_TRIE_H

#include "state.h"

#include <map>
#include <vector>


class HashTrie{
    public:
        
        HashTrie();
        virtual ~HashTrie();
        State * get_state(std::vector<std::pair<int,int> > & seq);
        void insert_state(std::vector<std::pair<int,int> > & seq,State * state);

    private:
        
        struct Node{
            std::map<std::pair<int,int>,Node*> adjacent;
            State * state;
            Node():state(NULL){/*std::cout << "hashtrie node.size(): " << adjacent.size() << "\n";*/}
            Node(State * state):state(state){
                
            }
        };

        Node * root = new Node();
    
};

#endif // HASH_TRIE_H