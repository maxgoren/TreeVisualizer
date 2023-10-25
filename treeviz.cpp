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

#include <iostream>
#include "TreeDraw.hpp"
#include "avl.hpp"
#include "binarysearchtree.hpp"
#include "redblack.hpp"
using namespace std;

bool hasAVLFlag(char* arg) {
    for (int i = 1; arg[i]; i++) {
        if (arg[i] == 'A')
            return true;
    }
    return false;
}

bool hasBSTFlag(char* arg) {
    for (int i = 1; arg[i]; i++) {
        if (arg[i] == 'B')
            return true;
    }
    return false;
}

bool hasRBFlag(char *arg) {
    for (int i = 1; arg[i]; i++) {
        if (arg[i] == 'R')
            return true;
    }
    return false;
}

bool hasLLRBFlag(char *arg) {
    for (int i = 1; arg[i]; i++) {
        if (arg[i] == 'L')
            return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    srand(time(0));
    TreeDraw<long, long> td;
    AVL<long, long> avl;
    BinarySearchTree<long, long> bst;
    LeftLeaningRedBlack<long, long> llrb;
    RedBlack<long, long> rb;
    for (int i = 0; i < atoi(argv[2]); i++) {
        int p = rand() % RAND_MAX;
        llrb.insert(p, i);
        rb.insert(p,i);
        avl.insert(p, i);
        bst.insert(p,i);
    }
    if (hasAVLFlag(argv[1]))
        td.mark(avl.rootNode(), avl.nil(), AVLT);
    if (hasBSTFlag(argv[1]))
        td.mark(bst.rootNode(), bst.nil(), BST);
    if (hasLLRBFlag(argv[1]))
        td.mark(llrb.rootNode(), llrb.nil(), REDBLACK);
    if (hasRBFlag(argv[1]))
        td.mark(rb.rootNode(), rb.nil(), REDBLACK);
    td.drawTree();
    return 0;
}