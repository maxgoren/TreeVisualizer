#ifndef treenode_hpp
#define treenode_hpp

const bool red = true;
const bool black = false;

template <class K, class V>
struct rbnode {
    K key;
    V value;
    int height;
    bool color;
    rbnode* left;
    rbnode* right;
    rbnode* parent;
    rbnode(K k, V v, bool c, rbnode* l, rbnode* r) {
        key = k; value = v; color = c; left = l; right = r; height = 0;
        parent = nullptr;
    }
    rbnode(K key_, V value_) {
        key = key_; value = value_;
        color = true;
        left = nullptr; right = nullptr;
        parent = nullptr;
        height = 0;
    }
};

#endif