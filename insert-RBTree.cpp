#include <iostream>
#include <fstream>

using namespace std;

#define RED 0
#define BLACK 1

ifstream input("input.txt");
ofstream output("output.txt");

template <class H>
class Node {
    public:
        H key;
        Node<H>* parent;
        Node<H>* left;
        Node<H>* right;
        int color;
};

template <class H>
class RBTree {
    private:
        Node<H>* root;

        void preorder(Node<H>* p);
        void inorder(Node<H>* p);
        void postorder(Node<H>* p);

        void trasplant(Node<H>* u, Node<H>* v);
    public:
        RBTree() : root(0) {}

        RBTree<H>* leftRotate(Node<H>* x);
        RBTree<H>* rightRotate(Node<H>* x);

        Node<H>* search(H key);
        RBTree<H>* insert(H key);
        void fix_insert(Node<H>* z);
        RBTree<H>* del(Node<H>* z);
        RBTree<H>* del(H key) { return del(search(key)); }

        Node<H>* minimum(Node<H>* z);
        Node<H>* massimum(Node<H>* z);
        Node<H>* successor(Node<H>* z);
        Node<H>* predecessor(Node<H>* z);

        Node<H>* getRoot() { return root; }

        int height(Node<H>* z);
        int height() { return height(root); }

        void print(char x);
};

template <class H>
void RBTree<H> :: preorder(Node<H>* p) {
    if(p) {
        output << "(" << p->key << " " << (p->color ? 'B' : 'R') << ") ";
        preorder(p->left);
        preorder(p->right);
    }
}

template <class H>
void RBTree<H> :: inorder(Node<H>* p) {
    if(p) {
        inorder(p->left);
        output << "(" << p->key << " " << (p->color ? 'B' : 'R') << ") ";
        inorder(p->right);
    }
}

template <class H>
void RBTree<H> :: postorder(Node<H>* p) {
    if(p) {
        postorder(p->left);
        postorder(p->right);
        output << "(" << p->key << " " << (p->color ? 'B' : 'R') << ") ";
    }
}

template <class H>
void RBTree<H> :: trasplant(Node<H>* u, Node<H>* v) {
    if(!u->parent) root = v;
    else if(u->parent->left == u) u->parent->left = v;
    else u->parent->right = v;

    if(v) v->parent = u->parent;
}

template <class H>
RBTree<H>* RBTree<H> :: leftRotate(Node<H>* x) {
    if(!x || !x->right) return this;
    Node<H>* y = x->right;
    x->right = y->left;
    if(y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if(!x->parent) root = y;
    else if(x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return this;
}

template <class H>
RBTree<H>* RBTree<H> :: rightRotate(Node<H>* x) {
    if(!x || !x->left) return this;
    Node<H>* y = x->left;
    x->left = y->right;
    if(y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if(!x->parent) root = y;
    else if(x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
    return this;
}

template <class H>
Node<H>* RBTree<H> :: search(H key) {
    Node<H>* tmp = root;
    while(tmp && tmp->key != key) {
        if(key <= tmp->key)
            tmp = tmp->left;
        else 
            tmp = tmp->right;
    }
    return tmp;
}

template <class H>
RBTree<H>* RBTree<H> :: insert(H key) {
    Node<H>* nuovo = new Node<H>;
    Node<H>* x = root, *y = NULL;

    nuovo->key = key;
    nuovo->left = nuovo->right = NULL;
    nuovo->color = RED;

    while(x) {
        y = x;
        if(key <= x->key) x = x->left;
        else x = x->right;
    }
    nuovo->parent = y;
    if(!y) root = nuovo;
    else if(key <= y->key) y->left = nuovo;
    else y->right = nuovo;

    fix_insert(nuovo);
    return this;
}

template <class H>
void RBTree<H> :: fix_insert(Node<H>* z) {
    if(z->parent && z->parent->color == BLACK) return ;
    if(root == z) {
        z->color = BLACK;
        return ;
    }
    Node<H>* padre = z->parent;
    Node<H>* nonno = padre->parent;
    Node<H>* zio = nonno->right;
    if(nonno->right == padre) zio = nonno->left;
    if(zio && zio->color == RED) {
        nonno->color = RED;
        padre->color = zio->color = BLACK;
        fix_insert(nonno);
        return ;
    }

    if(nonno->left == padre) {
        if(z == padre->right) {
            leftRotate(padre);
            padre = z;
            z = padre->left;
        }
        rightRotate(nonno);
        nonno->color = RED;
        padre->color = BLACK;
        return ;
    }
    else {
        if(z == padre->left) {
            rightRotate(padre);
            padre = z;
            z = padre->right;
        }
        leftRotate(nonno);
        nonno->color = RED;
        padre->color = BLACK;
        return ;
    }
}

template <class H>
RBTree<H>* RBTree<H> :: del(Node<H>* z) {
    if(!z) return this;
    else if(!z->left) trasplant(z, z->right);
    else if(!z->right) trasplant(z, z->left);
    else {
        Node<H>* s = successor(z);
        del(s);
        z->key = s->key;
    }
    return this;
}

template <class H>
Node<H>* minimum(Node<H>* z) {
    Node<H>* tmp = z;
    while(z && tmp->left) {
        tmp = tmp->left;
    }
    return tmp;
}

template <class H>
Node<H>* massimum(Node<H>* z) {
    Node<H>* tmp = z;
    while(z && tmp->right) {
        tmp = tmp->right;
    }
    return tmp;
}

template <class H>
Node<H>* RBTree<H> :: successor(Node<H>* z) {
    if(!z) return NULL;
    if(z->right) return minimum(z->right);

    Node<H>* y = z->parent;
    while(y && y->right == z) {
        z = y;
        y = y->parent;
    }
    return y;
}

template <class H>
Node<H>* RBTree<H> :: predecessor(Node<H>* z) {
    if(!z) return NULL;
    if(z->left) return massimum(z->left);

    Node<H>* y = z->parent;
    while(y && y->left == z) {
        z = y;
        y = y->parent;
    }
    return y;
}

template <class H>
int RBTree<H> :: height(Node<H>* z) {
    if(!z) return 0;
    int a = height(z->left), b = height(z->right);
    return 1 + (a > b ? a : b);
}

template <class H>
void RBTree<H> :: print(char x) {
    switch(x) {
        case 'r' : preorder(root); break;
        case 'n' : inorder(root); break;
        case 'o' : postorder(root); break;
    }
}

void insert_RBTree() {
    string tipo, ordine;
    int n;
    input >> tipo >> n >> ordine;
    if(tipo == "int") {
        RBTree<int>* a = new RBTree<int>();
        int x;
        for(int i = 0; i < n; i++) {
            input >> x;
            a->insert(x);
        }
        a->print(ordine[1]);
        output << endl;
    }
    if(tipo == "double") {
        RBTree<double>* a = new RBTree<double>();
        double x;
        for(int i = 0; i < n; i++) {
            input >> x;
            a->insert(x);
        }
        a->print(ordine[1]);
        output << endl;
    }
}

int main() {
    for(int i = 0; i < 100; i++)
        insert_RBTree();
}
