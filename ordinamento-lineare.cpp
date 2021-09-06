#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define INT 0
#define BOOL 1
#define CHAR 2
#define DOUBLE 3

ifstream input("input.txt");
ofstream output("output.txt"); 

void print(int* a, int n, int tipo) {
    for(int i = 0; i < n; i++)
        switch(tipo) {
            case 0 : output << a[i] << " "; break;
            case 1 : output << (bool)a[i] << " "; break;
            case 2 : output << (char)a[i] << " "; break;
            case 3 : output << (double)(a[i]/10.0) << " "; break;
        }
}

template <class H>
void printC(H* a, int n) {
    output << 0 << " ";
    bool cond = false;
    for(int i = 0; i < n; i++) {
        if(a[i] != 0) cond = true;
        if(cond) output << a[i] << " ";
    }
}

int* countingSort(int* a, int n, int k) {
    int* c = new int[k];
    int* b = new int[n];
    for(int i = 0; i < k; i++)
        c[i] = 0;
    for(int i = 0; i < n; i++)
        c[a[i]]++;
    for(int i = 1; i < k; i++)
        c[i] += c[i - 1];
    for(int i = 0; i < n; i++) {
        c[a[i]]--;
        b[c[a[i]]] = a[i];
    }
    printC(c, k);
    return b;
}

string convert(string str) {
    char* a = new char[str.length() + 2];
    int cont = 0;
    bool punto = false;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != '.')
            a[cont++] = str[i];
        else punto = true;
    }
    if(!punto) a[cont++] = '0';
    a[cont] = '\0';
    return a;

}

void metodo() {
    string tipo; int n;
    input >> tipo >> n;
    if(tipo == "int") {
        int a[n];
        input >> a[0];
        int max = a[0];
        for(int i = 1; i < n; i++) {
            input >> a[i];
            if(max < a[i]) max = a[i];
        }
        
        print(countingSort(a, n, max+1), n, INT);
        output << endl;
    }
    if(tipo == "bool") {
        int a[n];
        input >> a[0];
        int max = a[0];
        for(int i = 1; i < n; i++) {
            input >> a[i];
            if(max < a[i]) max = a[i];
        }
        
        print(countingSort(a, n, max+1), n, BOOL);
        output << endl;
    }
    if(tipo == "char") {
        int a[n]; char x;
        input >> x; a[0] = (int)x;
        int max = a[0];
        for(int i = 1; i < n; i++) {
            input >> x; a[i] = (int)x;
            if(max < a[i]) max = a[i];
        }
        
        print(countingSort(a, n, max+1), n, CHAR);
        output << endl;
    }
    if(tipo == "double") {
        int a[n]; string x;
        input >> x; a[0] = atoi(convert(x).c_str());
        int max = a[0];
        for(int i = 1; i < n; i++) {
            input >> x; a[i] = atoi(convert(x).c_str());
            if(max < a[i]) max = a[i];
        }
        
        print(countingSort(a, n, max+1), n, DOUBLE);
        output << endl;
    }
}

int main() {
    for(int i = 0; i < 100; i++)
        metodo();
}
