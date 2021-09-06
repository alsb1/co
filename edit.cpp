#include <iostream>
#include <fstream>

using namespace std;

template <class H>
H minimo(H a, H b) {
    return (a < b ? a : b);
}

template <class H>
H minimo(H a, H b, H c) {
    return minimo(minimo(a,b),c);
}

int** edit(string x, string y) {
    int n = x.length();
    int m = y.length();
    int** d = new int*[n+1];
    for(int i = 0; i < n+1; i++)
        d[i] = new int[m+1];
    for(int i = 1; i <= n; i++)
        d[i][0] = i;
    for(int j = 0; j <= m; j++)
        d[0][j] = j;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            d[i][j] = minimo(d[i-1][j-1] + (x[i-1] != y[j-1] ? 1 : 0),
                            d[i-1][j] + 1,
                            d[i][j-1] + 1);
                            
        }
    }
    //cout << d[n][m] << endl;
    return d;
}
void metodo(ifstream& input, ofstream& output) {
    int n, m;
    input >> n >> m;
    string x, y;
    input >> x >> y;
    int** d = edit(x,y);
    output << d[n][m] << endl; 
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
