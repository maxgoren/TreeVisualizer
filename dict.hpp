#ifndef dict_hpp
#define dict_hpp
#include <iostream>
#include "./src/include/treenode.hpp"
#include "kvpair.hpp"
#include "iterators.hpp"
using namespace std;

template <class K, class V>
class Dict {
    private:
        using link = rbnode<K,V>*;
        link root;
        int count;
        bool isRed(link h) {
            return h == nullptr ? false:h->color;
        }
        int size(link h) {
            return h == nullptr ? 0:h->N;
        }
        link rotL(link h) {
            link x = h->right;
            h->right = x->left;
            x->left = h;
            x->color = h->color;
            h->color = true;
            x->N = h->N;
            h->N = 1 + size(h->left) + size(h->right);
            return x;
        }
        link rotR(link h) {
            link x = h->left;
            h->left = x->right;
            x->right = h;
            x->color = h->color;
            h->color = true;
            x->N = h->N;
            h->N = 1 + size(h->left) + size(h->right);
            return x;
        }
        link colorFlip(link h) {
            h->color = !h->color;
            h->left->color = !h->left->color;
            h->right->color = !h->right->color;
            return h;
        }
        link makeDoubleRedStraight(link h) {
            if (isRed(h->left) && isRed(h->left->right)) {
                h->left = rotL(h->left);
            }
            if (isRed(h->right) && isRed(h->right->left)) {
                h->right = rotR(h->right);
            }
            return h;
        }
        link makeDoubleRedSiblings(link h) {
            if (isRed(h->left) && isRed(h->left->left))
                h = rotR(h);
            if (isRed(h->right) && isRed(h->right->right))
                h = rotL(h);
            return h;
        }
        link pushRedUp(link h) {
            if (isRed(h->left) && isRed(h->right))
                h = colorFlip(h);
            return h;
        }
        link balance(link h) {
            h = makeDoubleRedStraight(h);
            h = makeDoubleRedSiblings(h);
            h = pushRedUp(h);
            return h;
        }
        link putRB(link h, K key, V value) {
            if (h == nullptr)
                return new rbnode<K,V>(key, value);
            if (key < h->info.key()) h->left = putRB(h->left, key, value);
            else h->right = putRB(h->right, key, value);
            h->N = 1 + size(h->left) + size(h->right);
            return balance(h);
        }
        link min(link h) {
            if (h == nullptr)
                return h;
            link x = h;
            while (x->left != nullptr) x = x->left;
            return x;
        }
        link eraseMin(link h) {
            if (h == nullptr)
                return h;
            if (h->left == nullptr)
                return h->right;
            h->left = eraseMin(h->left);
            return h;
        }
        link eraseRB(link h, K key) {
            if (h == nullptr)
                return h;
            if (key < h->info.key())
                h->left = eraseRB(h->left, key);
            else if (key > h->info.key())
                h->right = eraseRB(h->right, key);
            else {
                link t = h;
                if (h->right == nullptr)
                    return h->left;
                h = min(t->right);
                h->right = eraseMin(t->right);
                h->left = t->left;
                delete t;
                count--;
            }
            return h;
        }
        void preorder(link h) {
            if (h != nullptr) {
                cout<<h->info.key()<<" ";
                preorder(h->left);
                preorder(h->right);
            }
        }
        bool validate(link h, int bh) {
            if (h == nullptr) {
                return bh == 0;
            }
            if (h->left != nullptr && h->info.key() < h->left->info.key()) return false;
            if (h->right != nullptr && h->info.key() > h->right->info.key()) return false;
            if (!isRed(h)) {
                bh--;
                if (isRed(h->left) && (isRed(h->left->left) || isRed(h->left->right)))
                    return false;
                if (isRed(h->right) && (isRed(h->right->right) || isRed(h->right->left)))
                    return false;
            } else if (isRed(h->left) && isRed(h->right)) {
                return false;
            } else if (isRed(h) && (isRed(h->left) || isRed(h->right))) {
                return false;
            }
            return validate(h->left, bh) && validate(h->right, bh);
        }
        link get(link h, K key) {
            if (h == nullptr)
               return nullptr;
            if (key == h->info.key())
                return h;
            return get((key < h->info.key()) ? h->left:h->right, key);
        }
        KVPair<K,V> nilInfo;
    public:
        Dict() {
            root = nullptr;
            count = 0;
        }
        void add(K key, V value) {
            root = putRB(root, key, value);
            root->color = false;
            count++;
        }
        void erase(K key) {
            root = eraseRB(root, key);
            if (root != nullptr)
                root->color =  false;
        }
        KVPair<K,V>& get(K key) {
            link t = get(root, key);
            return (t == nullptr) ? nilInfo:t->info;
        }
        link rootNode() {
            return root;
        }
        link nil() {
            return nullptr;
        }
        bool validateRB() {
            int bh = 0;
            link x = root;
            while (x != nullptr) {
                if (!isRed(x)) bh++;
                x = x->left;
            }
            return validate(root, bh);
        }
        void preorder() {
            preorder(root);
            cout<<endl;
        }
        DictIterator<K,V> iter() {
            return DictIterator<K,V>(root, count);
        }
        V& operator[](K key) {
            if (get(root, key) == nullptr)
                add(key, V());
            return get(root, key)->info.value();
        }
};

#endif