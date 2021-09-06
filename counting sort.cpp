#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H>
string print(H* a, int n) {
    stringstream out;
    for(int i = 0; i < n; i++) {
        out << a[i] << " ";
    }
    return out.str();
}

template <class H>
string printC(H* a, int n) {
    stringstream out;
    out << 0 << " ";
    bool cond = false;
    for(int i = 0; i < n; i++) {
        if(a[i] != 0) cond = true;
        if(cond) out << a[i] << " ";
    }
    return out.str();
}

template <class H>
void countingsort(H* a, int n, int k, ofstream& output) {
    H* c = new H[k];
    H* b = new H[n];
    for(int i = 0; i < k; i++) c[i] = 0;
    for(int j = 0; j < n; j++) c[a[j]] = c[a[j]] + 1;
    //c[i] adesso contiene il numero di elementi uguali a i.
    for(int i = 1; i < k; i++) c[i] = c[i] + c[i-1];
    //c[i] adesso contiene il numero di elementi minori o uguali a i.
    for(int j = n-1; j >= 0; j--) {
        c[a[j]] = c[a[j]] - 1;
        b[c[a[j]]] = a[j];
    }
    output << printC(c, k) << print(b,n) << endl;
}

void metodo(ifstream& input, ofstream& output) {
    int n;
    input >> n;
    int *a = new int[n];
    int max = -1;
    for(int i = 0; i < n; i++) {
        input >> a[i];
        if(a[i] > max) max = a[i];
    }
    countingsort(a,n,max+1,output);
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
