#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int N;

template <class H>
class MinHeap {
    private:
        H** A;
        int length;
        int heapsize;
        void heapify(int i);
        double compare(H* a, H* b) { return (*a) - (*b); }
        void swap(int i, int j);
        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1)|1; }
        int parent(int i) { return i >> 1; }
    public:
        MinHeap(int size);
        MinHeap(H** v, int n);
        void buildMinHeap();
        H* extractMin();
        MinHeap<H>* enqueue(H key);
        int size() { return heapsize; }
        string print() const;
};

template <class H>
void MinHeap<H> :: heapify(int i) {
    N++;
    int l = left(i);
    int r = right(i);
    int min = i;
    if(l <= heapsize && compare(A[i], A[l]) > 0) min = l;
    if(r <= heapsize && compare(A[min], A[r]) > 0) min = r;
    if(i != min) {
        swap(i,min);
        heapify(min);
    }
}

template <class H>
void MinHeap<H> :: swap(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <class H>
MinHeap<H> :: MinHeap(int size) {
    A = new H*[size];
    length = size;
    heapsize = 0;
}

template <class H>
MinHeap<H> :: MinHeap(H** v, int n) {
    A = v;
    length = n;
    heapsize = n-1;
}

template <class H>
void MinHeap<H> :: buildMinHeap() {
    for(int i = heapsize/2; i > 0; i--)
        heapify(i);
}

template <class H>
H* MinHeap<H> :: extractMin() {
    if(heapsize == 0) return NULL;
    swap(heapsize, 1);
    heapsize--;
    if(heapsize != 0) heapify(1);
    return A[heapsize+1];
}

template <class H>
MinHeap<H>* MinHeap<H> :: enqueue(H key) {
    if(heapsize == length-1) cout << "Array pieno\n";
    else {
        heapsize++;
        A[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && compare(A[i], A[parent(i)]) < 0) {
            swap(i, parent(i));
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
string print(H* a, int n) {
    stringstream out;
    for(int i = 0; i < n; i++)
        out << a[i] << " ";
    return out.str();
}

template <class H>
void heapsort(H* a, int n) {
    H** v = new H*[n+1];
    for(int i = 0; i < n; i++) v[i+1] = new H(a[i]);
    MinHeap<H>* m = new MinHeap<H>(v, n+1);
    m->buildMinHeap();
    for(int i = 0; i < n; i++)
        m->extractMin();
    for(int i = 0; i < n; i++) a[i] = *(v[i+1]);
}

void reverse_heapsort(ifstream& input, ofstream& output) {
    N = 0;
    string tipo; int n;
    input >> tipo >> n;
    if(tipo == "int") {
        int *a = new int[n];
        for(int i = 0; i < n; i++) {
            input >> a[i];
        }
        heapsort(a,n);
        output << N << " " << print(a,n);
    }
    if(tipo == "char") {
        char *a = new char[n];
        for(int i = 0; i < n; i++) {
            input >> a[i];
        }
        heapsort(a,n);
        output << N << " " << print(a,n);
    }
    if(tipo == "bool") {
        bool *a = new bool[n];
        for(int i = 0; i < n; i++) {
            input >> a[i];
        }
        heapsort(a,n);
        output << N << " " << print(a,n);
    }
    if(tipo == "double") {
        double *a = new double[n];
        for(int i = 0; i < n; i++) {
            input >> a[i];
        }
        heapsort(a,n);
        output << N << " " << print(a,n);
    }
    output << endl;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        reverse_heapsort(input, output);
}
