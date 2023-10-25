#ifndef avl_hpp
#define avl_hpp

template <class K, class V>
class AVL {
    private:
        using Node = rbnode<K,V>*;
        Node root;
        int count;
        int height(Node h) {
            return (h == nullptr) ? -1:h->height;
        }
        Node adjustheight(Node h) {
            h->height = 1+max(height(h->left), height(h->right));
            return h;
        }
        Node rotL(Node h) {
            Node x = h->right;
            h->right = x->left;
            x->left = h;
            h = adjustheight(h);
            x = adjustheight(x);
            lrcount++;
            return x;
        }
        Node rotR(Node h) {
            Node x = h->left; h->left = x->right;
            x->right = h;
            h = adjustheight(h);
            x = adjustheight(x);
            rrcount++;
            return x;
        }
        int balanceFactor(Node h) {
            return height(h->left) - height(h->right);
        }
        Node balance(Node h) {
            if (balanceFactor(h) < -1) {
                if (balanceFactor(h->right) > 0)
                    h->right = rotR(h->right);
                h = rotL(h);
            } else if (balanceFactor(h) > 1) {
                if (balanceFactor(h->left) < 0)
                    h->left = rotL(h->left);
                h = rotR(h);
            }
            return h;
        }
        Node insert(Node h, K key, V value) {
            if (h == nullptr) {
                return new rbnode<K,V>(key, value);
            }
            if (key < h->key) h->left = insert(h->left, key, value);
            else h->right = insert(h->right, key, value);
            h = adjustheight(h);
            return balance(h);
        }
        void inorder(Node h) {
            if (h == nullptr) return;
            inorder(h->left);
            cout<<h->key<<" ";
            inorder(h->right);
        }
        void visit(Node h) {
            if (h != nullptr) {
                cout<<h->key<<" ";
                visit(h->left);
                visit(h->right);
            }
        }
        int lrcount;
        int rrcount;
        void cleanup(Node h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
    public:
        AVL() {
            root = nullptr;
            count = 0;
            lrcount = 0;
            rrcount = 0;
        }
        ~AVL() {
            cleanup(root);
        }
        void insert(K key, V value) {
            root = insert(root, key, value);
            count++;
        }
        void show() {
            cout<<"Left rotations:  "<<lrcount<<endl;
            cout<<"Right rotations: "<<rrcount<<endl;
            cout<<"Nodes: "<<count<<endl;
            cout<<"Height: "<<1+height(root)<<endl;
        }
        int height() {
            return 1+height(root);
        }
        void sort(){
            inorder(root);
            cout<<endl;
        }
        Node rootNode() {
            return root;
        }
        Node nil() {
            return nullptr;
        }
};

#endif