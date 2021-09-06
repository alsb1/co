#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

#define PREORDER 0
#define INORDER 1
#define POSTORDER 2

ifstream input("input.txt");
ofstream output("output.txt");

template <class H>
class Nodo {
    public:
        Nodo(H k) : key(k), left(NULL), right(NULL), parent(NULL) {}
        Nodo(H k, Nodo<H>* l, Nodo<H>* r, Nodo<H>* p) : key(k), left(l), right(r), parent(p) {}
        H key;
        Nodo<H>* left;
        Nodo<H>* right;
        Nodo<H>* parent;
};

template <class H>
class BST {
    private:
        Nodo<H>* root;

        void preorder(Nodo<H>* p);
        void inorder(Nodo<H>* p);
        void postorder(Nodo<H>* p);

        void trapianta(Nodo<H>* u, Nodo<H>* v);
    public:
        BST() : root(NULL) {}

        BST<H>* insert(H key);
        BST<H>* del(Nodo<H>* z);
        Nodo<H>* search(H x);

        Nodo<H>* massimum(Nodo<H>* p);
        Nodo<H>* minimum(Nodo<H>* p);
        Nodo<H>* successor(Nodo<H>* p);
        Nodo<H>* predecessor(Nodo<H>* p);

        Nodo<H>* getRoot() { return root; }

        BST<H>* leftRotate(Nodo<H>* x);
        BST<H>* rightRotate(Nodo<H>* x);

        void print(int x); 
};

template <class H>
void BST<H> :: preorder(Nodo<H>* p) {
    if(p != NULL) {
        output << p->key << " ";
        preorder(p->left);
        preorder(p->right);
    }
}

template <class H>
void BST<H> :: inorder(Nodo<H>* p) {
    if(p != NULL) {
        inorder(p->left);
        output << p->key << " ";
        inorder(p->right);
    }
}

template <class H>
void BST<H> :: postorder(Nodo<H>* p) {
    if(p != NULL) {
        postorder(p->left);
        postorder(p->right);
        output << p->key << " ";
    }
}

template <class H>
void BST<H> :: trapianta(Nodo<H>* u, Nodo<H>* v) {
    if(u->parent == NULL) root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if(v != NULL) v->parent = u->parent;
}

template <class H>
BST<H>* BST<H> :: insert(H key) {
    Nodo<H>* nuovo = new Nodo<H>(key);
    Nodo<H>* x = root, *y = NULL;

    nuovo->left = nuovo->right = NULL;

    while(x != NULL) {
        y = x;
        if(key <= x->key) x = x->left;
        else x = x->right;
    }

    nuovo->parent = y;
    if(y == NULL) root = nuovo;
    else if(key <= y->key) y->left = nuovo;
    else y->right = nuovo;

    return this;
}

template <class H>
BST<H>* BST<H> :: del(Nodo<H>* z) {
    if(z == NULL) cout << "Nodo NULL\n";
    else if(z->left == NULL) trapianta(z, z->right);
    else if(z->right == NULL) trapianta(z, z->left);
    else {/*
        Nodo<H>* y = minimum(z->right);
        if(y->parent != z) {
            trapianta(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        trapianta(z, y);
        y->left = z->left;
        y->left->parent = y;*/
        Nodo<H>* s = successor(z);
        del(s);
        z->key = s->key;
    }
    
    return this;
}

template <class H>
Nodo<H>* BST<H> :: search(H key) {
    Nodo<H>* tmp = root;
    while(tmp != NULL && tmp->key != key) {
        if(key <= tmp->key) tmp = tmp->left;
        else tmp = tmp->right;
    }
    return tmp;
}

template <class H>
Nodo<H>* BST<H> :: massimum(Nodo<H>* p) {
    Nodo<H>* tmp = p;
    while(p != NULL && tmp->right != NULL) {
        tmp = tmp->right;
    }
    return tmp;
}

template <class H>
Nodo<H>* BST<H> :: minimum(Nodo<H>* p) {
    Nodo<H>* tmp = p;
    while(p != NULL && tmp->left != NULL)
        tmp = tmp->left;
    return tmp;
}

template <class H> 
Nodo<H>* BST<H> :: successor(Nodo<H>* p) {
    if(p == NULL) return NULL;
    else if(p->right != NULL) return minimum(p->right);

    Nodo<H>* y = p->parent;
    while(y != NULL && p == y->right) {
        p = y;
        y = y->parent;
    }
    return y;
}

template <class H>
Nodo<H>* BST<H> :: predecessor(Nodo<H>* p) {
    if(p == NULL) return NULL;
    else if(p->left != NULL) return massimum(p->left);

    Nodo<H>* y = p->parent;
    while(y != NULL && p == y->left) {
        p = y;
        y = y->parent;
    }
    return y;
}

template <class H>
void BST<H> :: print(int x) {
    switch(x) {
        case 0 : preorder(root); break;
        case 1 : inorder(root); break;
        case 2 : postorder(root); break;
    }
    output << endl;
}

template <class H>
BST<H>* BST<H> :: rightRotate(Nodo<H>* x) {
	if(x == NULL) return this; 
    if(x->left == NULL) return this;
    Nodo<H> *y = x->left;
    x->left = y->right;
    
    if(y->right != NULL) 
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL) root = y;
    else if(x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
	return this;
}

template <class H>
BST<H>* BST<H> :: leftRotate(Nodo<H>* x) {
	if(x == NULL || x->right == NULL) return this;
    Nodo<H> *y = x->right;
    x->right = y->left;

    if(y->left != NULL) 
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL) root = y;
    else if(x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
	return this;
}

void rotazioni_BST() {
    string tipo; input >> tipo;
    int n; input >> n;
    int m; input >> m;
    string stampa; input >> stampa;
    if(tipo == "int") {
        BST<int> *b = new BST<int>();
        for(int i = 0; i < n; i++) {
            string oper; input >> oper;
            if(oper.substr(0,4) == "ins:") 
                b->insert(atoi(oper.substr(4).c_str()));
            else 
                b->del(b->search(atoi(oper.substr(5).c_str())));
        }
        for(int i = 0; i < m; i++) {
            string rot; input >> rot;
            if(rot.substr(0,5) == "left:") 
                b->leftRotate(b->search(atoi(rot.substr(5).c_str())));
            else 
                b->rightRotate(b->search(atoi(rot.substr(6).c_str())));
        }
        if(stampa == "inorder") b->print(INORDER);
        else if(stampa == "preorder") b->print(PREORDER);
        else b->print(POSTORDER);
    }
    if(tipo == "double") {
        BST<double> *b = new BST<double>();
        for(int i = 0; i < n; i++) {
            string oper; input >> oper;
            if(oper.substr(0,4) == "ins:")
                b->insert(atof(oper.substr(4).c_str()));
            else {
                b->del(b->search(atof(oper.substr(5).c_str())));
            }
        }
        for(int i = 0; i < m; i++) {
            string rot; input >> rot;
            if(rot.substr(0,5) == "left:")
                b->leftRotate(b->search(atof(rot.substr(5).c_str())));
            else {
                b->rightRotate(b->search(atof(rot.substr(6).c_str())));
            }
        }
        if(stampa == "inorder") b->print(INORDER);
        else if(stampa == "preorder") b->print(PREORDER);
        else b->print(POSTORDER);
    }
}

int main() {
    for(int i = 0; i < 100; i++)
        rotazioni_BST();
}
