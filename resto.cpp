#include <iostream>
#include <fstream>

using namespace std;

void sort(int *a, int n) {
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            if(a[i] > a[j]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
}

void print_resto(int* t, int n, int r, int** m) {
    int k = n-1;
    int i = r;
    while(i > 0) {
        if(k == 1 || m[k][i] < m[k-1][i]) {
            cout << t[k] << " ";
            i = i - t[k];
        }
        else 
            k = k - 1;
    }
    cout << endl;
}

// t dev'essere ordinato
int resto(int r, int* t, int n) {//r = resto e t[n] array dei tagli disponibili
    int ** m = new int*[n];
    for(int i = 0; i < n; i++)
        m[i] = new int[r+1];

    for(int i = 0; i <= r; i++)
        m[0][i] = i;
    for(int k = 1; k < n; k++)
        m[k][0] = 0;
    for(int k = 1; k < n; k++) {
        for(int i = 1; i <= r; i++) {
            m[k][i] = m[k-1][i]; 
            if(i >= t[k] && 1 + m[k][i - t[k]] < m[k][i])
                m[k][i] = 1 + m[k][i - t[k]];
        }
    }
    print_resto(t, n, r, m);
    return m[n-1][r];
}

void metodo(ifstream& input, ofstream& output) {
    int r, n;
    input >> r >> n;
    int *t = new int[n];
    for(int i = 0; i < n; i++)  
        input >> t[i];
    sort(t, n);
    output << resto(r, t, n) << endl;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
