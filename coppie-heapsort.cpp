#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int N;

template <class H>
class Element {
    public:
        H x, y;
};

template <class H>
bool operator<(const Element<H> i, const Element<H> j) {
    return (i.x < j.x || (i.x == j.x && i.y < j.y));
}

template <class H>
bool operator==(const Element<H> i, const Element<H> j) {
    return (i.x == j.x && i.y == j.y);
}

template <class H>
bool operator<=(const Element<H> i, const Element<H> j) {
    return (i < j || i == j);
}

template <class H>
bool operator>(const Element<H> i, const Element<H> j) {
    return !(i <= j);
}

template <class H>
Element<H> operator-(const Element<H> i, const Element<H> j) {
    Element<H> a; a.x = i.x - j.x; a.y = i.y - j.y;
    return a;
}

template <class H>
ostream& operator<<(ostream& out, const Element<H>& a) {
    out << "(" << a.x << " " << a.y << ")";
    return out;
}

template <class H>
class MaxHeap {
    private:
        H** a;
        int length;
        int heapsize;
        void swap(int i, int j);
        //double compare(H* a, H* b) { return (*a) - (*b); }
        void heapify(int i);
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
};

template <class H>
void MaxHeap<H> :: swap(int i, int j) {
    H* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

template <class H>
void MaxHeap<H> :: heapify(int i) {
    N++;
    int l = left(i);
    int r = right(i);
    int max = i;
    if(l <= heapsize && (*(a[i])) < (*(a[l])) ) max = l;
    if(r <= heapsize && (*(a[max])) < (*(a[r])) ) max = r;
    if(max != i) {
        swap(i, max);
        heapify(max);
    }
}

template <class H>
MaxHeap<H> :: MaxHeap(int size) {
    a = new H*[size];
    length = size;
    heapsize = 0;
}

//Presuppone che il primo indice no venghi considerato
template <class H>
MaxHeap<H> :: MaxHeap(H** v, int n) {
    a = v;
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
    swap(1, heapsize); 
    heapsize--;
    if(heapsize != 0) heapify(1);
    return a[heapsize + 1];
}

template <class H>
MaxHeap<H>* MaxHeap<H> :: enqueue(H key) {
    if(heapsize != length - 1) {
        heapsize++;
        a[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && (*(a[i])) > (*(a[parent(i)])) ) {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    return this;
}

template <class H>
void heapsort(H* a, int n) { 
    H** v = new H*[n+1]; 
    for(int i = 0; i < n; i++)
        v[i+1] = new H(a[i]); 
    MaxHeap<H>* m = new MaxHeap<H>(v, n+1);
    m->buildMaxHeap(); 
    for(int i = 0; i < n; i++)
        m->extractMax();
    for(int i = 0; i < n; i++)
        a[i] = *(v[i+1]);
}

template <class H>
void print(H* a, int n, ofstream& output) {
    for(int i = 0; i < n; i++)
        output << a[i] << " ";
    output << endl;
} 

void metodo(ifstream& input, ofstream& output) {
    N = 0;
    string tipo;
    int n;
    input >> tipo >> n;
    
    string str;
    if(tipo == "int") {
        Element<int> a[n];
        for(int i = 0; i < n; i++) {
            input >> str;
            a[i].x = atoi(str.substr(1).c_str());
            input >> str;
            a[i].y = atoi(str.substr(0, str.length()-1).c_str());
        }
        heapsort(a, n);
        
        output << N << " ";
        print(a, n, output);
    }
    if(tipo == "bool") {
        Element<bool> a[n];
        for(int i = 0; i < n; i++) {
            input >> str;
            a[i].x = atoi(str.substr(1).c_str());
            input >> str;
            a[i].y = atoi(str.substr(0, str.length()-1).c_str());
        }
        heapsort(a, n);
        
        output << N << " ";
        print(a, n, output);
    }
    if(tipo == "char") {
        Element<char> a[n];
        for(int i = 0; i < n; i++) {
            input >> str;
            a[i].x = str[1];
            input >> str;
            a[i].y = str[0];
        }
        heapsort(a, n);
        
        output << N << " ";
        print(a, n, output);
    }
    if(tipo == "double") {
        Element<double> a[n];
        for(int i = 0; i < n; i++) {
            input >> str;
            a[i].x = atof(str.substr(1).c_str());
            input >> str;
            a[i].y = atof(str.substr(0, str.length()-1).c_str());
        }
        heapsort(a, n);
        
        output << N << " ";
        print(a, n, output);
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
