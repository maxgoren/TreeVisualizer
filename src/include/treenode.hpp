#ifndef treenode_hpp
#define treenode_hpp

const bool red = true;
const bool black = false;

template <class K, class V>
struct rbnode {
    K key;
    V value;
    int id;
    bool color;
    int N;
    rbnode* left;
    rbnode* right;

    rbnode(K key_, V value_) {
        key = key_; value = value_;
        color = true;
        left = nullptr; right = nullptr;
        N = 0;
    }
    rbnode() {
        color = true;
    }
};

#endif
