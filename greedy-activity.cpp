#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template <class H>
class Element {
    public:
        Element<H>* p;
        H key;
};

template <class H>
class List {
    Element<H>* first;
    int size;
    public:
        List() : first(0), size(0){}
        List<H>* insert(H key) {
            Element<H>* newEl = new Element<H>;
            newEl->p = first;
            newEl->key = key;
            first = newEl;
            size++;
            return this;
        }
        void print() {
            Element<H>* tmp = first;
            while(tmp != NULL) {
                cout << tmp->key << " ";
                tmp = tmp->p;
            }
            cout << endl;
        }
        int getSize() { return size; }

};

void sort(int* s, int* f, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(f[i] > f[j]) {
                int tmp = f[i];
                f[i] = f[j];
                f[j] = tmp;
                
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}

int greedy_activity(int* s, int* f, int n){
    List<int>* a = new List<int>();
    a->insert(0);
    int i = 0, cont = 1;
    for(int m = 1; m < n; m++)
        if(s[m] >= f[i]) {
            a->insert(m);
            i = m;
        }
    a->print();
    return a->getSize(); 
}

void metodo(ifstream& input, ofstream& output) {
     int n;
     input >> n;
     int* s = new int[n];
     int* f = new int[n];
     string x;
     for(int i = 0; i < n; i++) {
        input >> x;
        s[i] = atoi(x.substr(1).c_str());
        input >> x;
        f[i] = atoi(x.substr(0, x.length()-1 ).c_str());
     }
     sort(s, f, n);
     output << greedy_activity(s, f, n) << endl; cout << endl;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
