#ifndef treenode_hpp
#define treenode_hpp
#include "kvpair.hpp"
const bool red = true;
const bool black = false;

template <class K, class V>
struct rbnode {
    KVPair<K,V> info;
    int id;
    bool color;
    int N;
    rbnode* left;
    rbnode* right;
    rbnode(K key_, V value_) : info(key_, value_) {
        color = true;
        left = nullptr; right = nullptr;
        N = 0;
    }
    rbnode() {
        color = true;
    }
};

#endif
