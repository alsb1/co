#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int N;

template <class H>
class MaxHeap {
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
        MaxHeap(int size);
        MaxHeap(H** v, int n);
        void buildMaxHeap();
        H* extractMax();
        MaxHeap<H>* enqueue(H key);
        int size() { return heapsize; }
        string print() const;
};

template <class H>
void MaxHeap<H> :: heapify(int i) {
    N++;
    int l = left(i);
    int r = right(i);
    int max = i;
    if(l <= heapsize && compare(A[i], A[l]) < 0) max = l;
    if(r <= heapsize && compare(A[max], A[r]) < 0) max = r;
    if(i != max) {
        swap(i,max);
        heapify(max);
    }
}

template <class H>
void MaxHeap<H> :: swap(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <class H>
MaxHeap<H> :: MaxHeap(int size) {
    A = new H*[size];
    length = size;
    heapsize = 0;
}

template <class H>
MaxHeap<H> :: MaxHeap(H** v, int n) {
    A = v;
    length = n;
    heapsize = n-1;
}

template <class H>
void MaxHeap<H> :: buildMaxHeap() {
    for(int i = heapsize/2; i > 0; i--)
        heapify(i);
}

template <class H>
H* MaxHeap<H> :: extractMax() {
    if(heapsize == 0) return NULL;
    swap(heapsize, 1);
    heapsize--;
    if(heapsize != 0) heapify(1);
    return A[heapsize+1];
}

template <class H>
MaxHeap<H>* MaxHeap<H> :: enqueue(H key) {
    if(heapsize == length-1) cout << "Array pieno\n";
    else {
        heapsize++;
        A[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && compare(A[i], A[parent(i)]) > 0) {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    return this;
}

template <class H>
string MaxHeap<H> :: print() const {
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
    MaxHeap<H>* m = new MaxHeap<H>(v, n+1);
    m->buildMaxHeap();
    for(int i = 0; i < n; i++)
        m->extractMax();
    for(int i = 0; i < n; i++) a[i] = *(v[i+1]);
}

void max_heap(ifstream& input, ofstream& output) {
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
        max_heap(input, output);
}
