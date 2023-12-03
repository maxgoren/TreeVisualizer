/*

MIT License

Copyright (c) 2023 Max Goren

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef redblack_hpp
#define redblack_hpp
#include <vector>
#include <limits>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "treenode.hpp"
using namespace std;

//Top down single pass 2-3-4 RedBlack tree
template <class K, class V>
class RedBlack {
    public:
        using nodeptr = rbnode<K,V>*;
    private:
        int lrcount;
        int rrcount;
        int splitcount;
        nodeptr head, z;
        nodeptr x, p, g, gg;
        nodeptr rotate(K key, nodeptr y) {
            nodeptr c, gc;
            c = (key < y->key) ? y->left:y->right;
            if (key < c->key) {
                rrcount++;
                gc = c->left; c->left = gc->right; gc->right = c;
            } else {
                lrcount++;
                gc = c->right; c->right = gc->left; gc->left = c;
            }
            if (key < y->key) y->left = gc; else y->right = gc;
            return gc;
        }
        void split(K key) {
            splitcount++;
            x->color = red; x->left->color = black; x->right->color = black;
            if (p->color) {
                g->color = red;
                if (key < p->key != key < g->key) p = rotate(key, g);
                x = rotate(key, gg);
                x->color = black;
            }
        }
        int height(nodeptr h) {
            if (h == z)
                return -1;
            return 1 + max(height(h->left), height(h->right));
        }
        int n;
        void cleanup(nodeptr h) {
            if (h != z) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
    public:
        RedBlack() {
            z = new rbnode<K,V>(std::numeric_limits<K>::max(), std::numeric_limits<V>::max(), false, nullptr, nullptr);
            z->right = z; z->left = z;
            head = new rbnode<K,V>(std::numeric_limits<K>::min(), std::numeric_limits<V>::min(), false,z,z);
            n = 0; lrcount = 0; rrcount = 0; splitcount = 0;
        }
        ~RedBlack() {
            cleanup(head->right);
            delete head;
            delete z;
        }
        void insert(K key, V value) {
            x = head; p = x; g = x;
            while (x != z) {
                gg = g; g = p; p = x;
                x = (key < x->key) ? x->left:x->right;
                if (x->left->color && x->right->color)
                    split(key);
            }
            x = new rbnode<K,V>(key, value, true, z, z);
            if (key < p->key) p->left = x; else p->right = x;
            split(key);
            head->right->color = false;
            n++;
        }
        int size() {
            return n;
        }
        int height() {
            return 1+height(head->right);
        }
        nodeptr rootNode() {
            return head->right;
        }
        nodeptr nil() {
            return z;
        }
};


//Bottom up 2-3 Left Leaning Red/Black Tree
template <class T, class T2>
class LeftLeaningRedBlack {
    private:
    using node = rbnode<T,T2>;
        node* root;
        bool isRed(node* h) { return (h == nullptr) ? false:(h->color == red); }

        void left_rotate(node *x) {
            node *y = x->right;
            if (y) {
                x->right = y->left;
                if (y->left) y->left->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->left = x;
            x->parent = y;
            y->color = x->color;
            x->color = red;
        }
  
        void right_rotate(node *x) {
            node *y = x->left;
            if (y) {
                x->left = y->right;
                if (y->right) y->right->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->right = x;
            x->parent = y;
            y->color = x->color;
            x->color = red;
        }
        void visit(node* x) {
            if (x) {
                cout<<x->key<<" ";
                visit(x->left);
                visit(x->right);
            }
        }
        void balance(node* x) {
            while (x != nullptr) {
                node *y = x;
                if (isRed(y->right) && !isRed(y->left)) left_rotate(y);
                if (isRed(y->left) && isRed(y->left->left)) right_rotate(y);
                if (isRed(y->right) && isRed(y->left)) {
                    y->color = red;
                    y->left->color = black;
                    y->right->color = black;
                }
                x = x->parent;
            }
        }
        void cleanup(node* h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
    public:
        LeftLeaningRedBlack() {
            root = nullptr;
        }
        ~LeftLeaningRedBlack() {
            cleanup(root);
        }
        void insert(T key, T2 value) {
            node* x = root;
            node* p = x;
            while (x) {
                p = x;
                x = (key < x->key) ? x->left:x->right;
            }
            x = new node(key, value);
            if (!p) root = x;
            else if (key < p->key) p->left = x;
            else p->right = x;
            x->parent = p;
            balance(x);
            root->color = black;
        }
        void show() {
            visit(root);
            cout<<endl;
        }
        bool contains(T key) {
            node* x = root;
            while (x != nullptr) {
                if (key == x->key)
                    return true;
                x = (key < x->key) ? x->left:x->right;
            }
            return false;
        }
        node* rootNode() {
            return root;
        }
        node* nil() {
            return nullptr;
        }
};

#endif
