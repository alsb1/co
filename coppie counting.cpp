#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

class Element {
    public:
        int x, y;
};

void print(Element* a, int n) {
    for(int i = 0; i < n; i++)
        output << "(" << double(a[i].x)/10.0 << " " << double(a[i].y)/10.0 << ") ";
}

void printC(int* a, int n) {
    output << 0 << " ";
    bool cond = false;
    for(int i = 0; i < n ; i++) {
        if(a[i] != 0) cond = true;
        if(cond) output << a[i] << " ";
    }
}

Element* countingSort(Element* a, int n, int k) {
    int* c = new int[k];
    Element* b = new Element[n];
    for(int i = 0; i < k; i++)
        c[i] = 0;
    for(int i = 0; i < n; i++)
        c[a[i].x]++;
    for(int i = 1; i < k; i++)
        c[i] += c[i-1];
    for(int i = n-1; i > -1; i--) {
        c[a[i].x]--;
        b[c[a[i].x]] = a[i];
    }
    printC(c, k);
    return b;
}

string convert(string x) {
    char* a = new char[x.length() + 2];
    int cont = 0;
    bool punto = true;
    for(int i = 0; i < x.length(); i++) {
        if(x[i] != '.')
            a[cont++] = x[i];
        else punto = false;
    }
    if(punto) a[cont++] = '0';
    a[cont] = '\0';
    return a;
}

void coppie_counting() {
    int n; input >> n;
    Element* a = new Element[n];
    string str; input >> str;
    a[0].x = atoi(convert(str.substr(1)).c_str());
    input >> str;
    a[0].y = atoi(convert(str.substr(0,str.length()-1)).c_str());
    
    int max = a[0].x;
    for(int i = 1; i < n; i++) {
        string str; input >> str;
        a[i].x = atoi(convert(str.substr(1)).c_str());
        input >> str;
        a[i].y = atoi(convert(str.substr(0,str.length()-1)).c_str());

        if(a[i].x > max) max = a[i].x;
    }
    print(countingSort(a, n, max+1), n);
    output << endl;
}

int main() {
    for(int i = 0; i < 100; i++)
        coppie_counting();
}
