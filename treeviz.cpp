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
#include "src/include/TreeDraw.hpp"
#include "dict.hpp"
#include "src/example/avl.hpp"
using namespace std;


int main(int argc, char *argv[]) {
    srand(time(0));
    TreeDraw<char, long> td;
    Dict<char, long> rb;
    AVL<char, long> avl;
    int prev = 0, curr = 1;
    string sed = "ASEARCHINGEXAMPLEWITHALOTOFKEYS";
    for (int i = 0; i < 66; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
        if (i < sed.length()) {
            rb.add(sed[i],i);
            avl.insert(sed[i], i);
        } else {
            int p = rand() % 99;
            rb.add(p, i);
            avl.insert(p, i);
        }
        if (i == 33) {
            td.mark(rb.rootNode(), rb.nil(), REDBLACK);
            td.mark(avl.rootNode(), avl.nil(), AVLT);
        }
    }
    td.mark(rb.rootNode(), rb.nil(), REDBLACK);
    td.mark(avl.rootNode(), avl.nil(), AVLT);
    td.drawTree();
    return 0;
}

