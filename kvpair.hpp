#ifndef kvpair_hpp
#define kvpair_hpp

template <class K, class V>
class KVPair {
    private:
        K _key;
        V _value;
        bool _empty;
    public:
        KVPair(K k, V v) {
            _key = k;
            _value = v;
            _empty = false;
        }
        KVPair() { _empty = true; }
        void clear() { 
            _empty = true;
            _key = K();
            _value = V();
        }
        bool operator==(const KVPair& o) const {
            if (_empty && o._empty)
                return true;
            return _key == o._key;
        }
        bool operator!=(const KVPair& o) const {
            return !(*this==o);
        }
        const K& key() const { return _key; }
        V& value() { return _value; }
        bool empty() { return _empty; }
        void setValue(V val) {
            _value = val;
        }
};

#endif