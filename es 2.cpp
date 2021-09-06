#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H>
class MinHeap {
    private:
        H** A;
        int length;
        int heapsize;
        void swap(int i, int j);
        double compare(H* a,H* b) { return (*a) - (*b); }
        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1)|1; }
        int parent(int i) { return i >> 1; }
        void heapify(int i);
    public:
        MinHeap(int size);
        MinHeap(H** V, int n);
        void buildMinHeap();
        H* extractMin();
        MinHeap<H>* enqueue(H key);
        int size() { return heapsize; }
        string print() const;
};

template <class H>
MinHeap<H> :: MinHeap(int size) {
    A = new H*[size];
    length = size;
    heapsize = 0;
}

template <class H>
MinHeap<H> :: MinHeap(H** V, int n) {
    A = V;
    length = n;
    heapsize = n-1;
}

template <class H>
void MinHeap<H> :: swap(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <class H>
void MinHeap<H> :: heapify(int i) {
    int l = left(i);
    int r = right(i);
    int min = i;
    if(l <= heapsize && compare(A[l], A[i]) < 0) min = l;
    if(r <= heapsize && compare(A[r], A[min]) < 0) min = r;
    if(min != i) {
        swap(i, min);
        heapify(min);
    }
}

template <class H>
void MinHeap<H> :: buildMinHeap() {
    for(int i = heapsize/2; i > 0; i--)
        heapify(i);
}

template <class H>
H* MinHeap<H> :: extractMin() {
    if(heapsize == 0) return NULL;
    swap(1,heapsize);
    heapsize--;
    heapify(1);
    return A[heapsize + 1];
}

template <class H>
MinHeap<H>* MinHeap<H> :: enqueue(H key) {
    if(heapsize == length-1) cout << "Array pieno\n";
    else {
        heapsize += 1;
        A[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && compare(A[i], A[parent(i)]) < 0) {
            swap(i,parent(i));
            i = parent(i);
        }
    }
    return this;
}

template <class H>
string MinHeap<H> :: print() const {
    stringstream out;
    for(int i = 1; i <= heapsize; i++)
        out << *(A[i]) << " ";
    return out.str();
}

template <class H> 
ostream& operator<<(ostream& out, const MinHeap<H> &a) {
    out << a.print();
    return out;
}


void metodo(ifstream &input, ofstream &output) {
    string tipo;
    int n;
    input >> tipo;
    input >> n; 
    if(tipo == "int") {
        int **a = new int*[n+1];
        int x;
        for(int i = 1; i <= n; i++) {
            input >> x;
            a[i] = new int(x);
        }
        
        MinHeap<int> *m = new MinHeap<int>(a,n+1);
        m->buildMinHeap();
        output << m->print() << endl;
    }
    if(tipo == "bool") {
        bool **a = new bool*[n+1];
        bool x;
        for(int i = 1; i <= n; i++) {
            input >> x;
            a[i] = new bool(x);
        }
        
        MinHeap<bool> *m = new MinHeap<bool>(a,n+1);
        m->buildMinHeap();
        output << m->print() << endl;
    }
    if(tipo == "char") {
        char **a = new char*[n+1];
        char x;
        for(int i = 1; i <= n; i++) {
            input >> x;
            a[i] = new char(x);
        }
        
        MinHeap<char> *m = new MinHeap<char>(a,n+1);
        m->buildMinHeap();
        output << m->print() << endl;
    }
    if(tipo == "double") {
        double **a = new double*[n+1];
        double x;
        for(int i = 1; i <= n; i++) {
            input >> x;
            a[i] = new double(x);
        }

        MinHeap<double> *m = new MinHeap<double>(a,n+1); 
        m->buildMinHeap();
        output << m->print() << endl;
    }
}


int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
