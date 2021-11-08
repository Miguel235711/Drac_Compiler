#ifndef HASH_TRIE_H
#define HASH_TRIE_H

#include "state.h"

#include <unordered_map>
#include <vector>


class HashTrie{
    public:
        
        HashTrie();
        virtual ~HashTrie();
        State * get_state(std::vector<int> & seq);
        void insert_state(std::vector<int> & seq,State * state);

    private:
        
        struct Node{
            std::unordered_map<int,Node*> adjacent;
            State * state;
            Node():state(NULL){}
            Node(State * state):state(state){}
        };

        Node * root = new Node();
    
};

#endif // HASH_TRIE_H