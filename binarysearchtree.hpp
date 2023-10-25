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
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treenode.hpp"
template <class K, class V>
class BinarySearchTree {
    private:
        using Node = rbnode<K,V>*;
        Node root;
        int count;
        void cleanup(Node h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
        Node insert(Node h, K key, V value) {
            if (h == nullptr) {
                count++;
                return new rbnode<K,V>(key, value);
            }
            if (key < h->key) h->left = insert(h->left, key, value);
            else h->right = insert(h->right, key, value);
            return h;
        }
    public:
        BinarySearchTree() {
            root = nullptr;
            count = 0;
        }
        ~BinarySearchTree() {
            cleanup(root);
        }
        void insert(K key, V value) {
            root = insert(root, key, value);
            count++;
        }
        int size() {
            return count;
        }
        bool empty() {
            return root == nullptr;
        }
        Node rootNode() {
            return root;
        }
        Node nil() {
            return nullptr;
        }
};

#endif