#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define INF 2147483647

ifstream input("input.txt");
ofstream output("output.txt");

int matrix_chain(int* p, int n) {
    int m[n+1][n+1];
    int s[n][n+1];

    for(int i = 1; i <= n; i++) m[i][i] = 0;

    for(int l = 2; l <= n; l++)
        for(int i = 1; i <= n-l+1; i++) {
            int j = i + l - 1;
            m[i][j] = INF;
            for(int k = i; k <= j-1; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    return m[1][n];
}

void metodo() {
    int n;
    input >> n;
    int* p = new int[n+1];
    string x;
    for(int i = 0; i < n; i++) {
        input >> x;
        if(x[2] == 'x') p[i] = atoi(x.substr(1,1).c_str());
        else p[i] = atoi(x.substr(1,2).c_str());
    }

    if(x[2] == 'x') {
        if(x[4] == ')')
            p[n] = atoi(x.substr(3,1).c_str());
        else
            p[n] = atoi(x.substr(3,2).c_str());
    }
    else { 
        if(x[5] == ')')
            p[n] = atoi(x.substr(4,1).c_str());
        else
            p[n] = atoi(x.substr(4,2).c_str());
    }

    output << matrix_chain(p,n) << endl;;
}

int main() {
    for(int i = 0; i < 100; i++)
        metodo();
}
