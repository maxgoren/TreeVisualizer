#ifndef iterators_hpp
#define iterators_hpp
#include "src/include/treenode.hpp"

template <class K, class V>
class DictIterator {
    private:
        using link = rbnode<K,V>*;
        link curr;
        int pos;
        int size(link h) {
            return h == nullptr ? 0:h->n;
        }
        KVPair<K,V>& select(link h, int k) {
            if (h == nullptr) return nilInfo;
            int t = size(h->left);
            if (t > k) return select(h->left, k);
            else if (t < k) return select(h->right, k - t - 1);
            else return h->info;
        }
        KVPair<K,V> nilInfo;
        int n;
    public:
        DictIterator(link start, int max) {
            curr = start; pos = 0;
            n = max;
        }
        bool done() {
            return pos >= n;
        }
        void next() {
            pos++;
        }
        KVPair<K,V> get() {
            return select(curr, pos);
        }
};

#endif