#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H>
class Heap {
    public:
        Heap(int size);
        Heap(H** V, int size);
        void buildHeap();
        H* extract();
        Heap<H>* enqueue(H key);
        int size() {return heapsize;}
        string print() const ;
    private:
        H **A;
        int length;
        int heapsize;
        double compare(H *a, H *b) {return (*a) - (*b);}
        int left(int i) {return i << 1;}
        int right(int i) {return (i << 1)|1;}
        int parent(int i) {return i >> 1;}
        void swap(int i, int j);
        void heapify(int i);
};

template <class H>
Heap<H> :: Heap(int size) {
    A = new H*[size];
    length = size;
    heapsize = 0;
}

template <class H>
Heap<H> :: Heap(H** V, int size) {
    A = V;
    length = size;
    heapsize = size-1;
}

template <class H>
void Heap<H> :: swap(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <class H>
void Heap<H> :: heapify(int i) {
    int l = left(i);
    int r = right(i);
    int max = i;
    if(l <= heapsize && compare(A[i], A[l]) < 0) max = l;
    if(r <= heapsize && compare(A[max], A[r]) < 0) max = r;
    if(max != i) {
        swap(i,max);
        heapify(max);
    }
}

template <class H>
void Heap<H> :: buildHeap() {
    for(int i = heapsize/2; i > 0; i--)
        heapify(i);
}

template <class H>
H* Heap<H> :: extract() {
    if(heapsize == 0) return NULL;
    swap(1, heapsize);
    heapsize--;
    heapify(1);
    return A[heapsize + 1];
}

template <class H>
Heap<H>* Heap<H> :: enqueue(H key) {
    if(heapsize != length - 1) {
        heapsize += 1;
        A[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && compare(A[i],A[parent(i)]) > 0) {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    return this;
}

template <class H>
string Heap<H> :: print() const {
    stringstream out;
    for(int i = 1; i <= heapsize; i++)
        out << *(A[i]) << " ";
    return out.str();
}

template <class H>
ostream& operator<<(ostream& out, const Heap<H>& a) {
    out << a.print();
    return out;
}

void metodo(ifstream& input, ofstream& output) {
    string tipo;
    input >> tipo; 
    int n;
    input >> n;
    if(tipo == "int") {
        int **a = new int*[n+1];
        int x;
        for(int i = 1; i < n+1; i++) {
            input >> x;
            a[i]  = new int(x);
        }
        Heap<int> *B = new Heap<int>(a, n+1);

        B->buildHeap();
        output << B->print() << endl;
    }
    if(tipo == "char") {
        char **a = new char*[n+1];
        char x;
        for(int i = 1; i < n+1; i++) {
            input >> x;
            a[i]  = new char(x);
        }
        Heap<char> *B = new Heap<char>(a, n+1);

        B->buildHeap();
        output << B->print() << endl;
    }
    if(tipo == "bool") {
        bool **a = new bool*[n+1];
        bool x;
        for(int i = 1; i < n+1; i++) {
            input >> x;
            a[i]  = new bool(x);
        }
        Heap<bool> *B = new Heap<bool>(a, n+1);

        B->buildHeap();
        output << B->print() << endl;
    }
    if(tipo == "double") {
        double **a = new double*[n+1];
        double x;
        for(int i = 1; i < n+1; i++) {
            input >> x;
            a[i]  = new double(x);
        }
        Heap<double> *B = new Heap<double>(a, n+1);

        B->buildHeap();
        output << B->print() << endl;
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)  
        metodo(input, output);
}
