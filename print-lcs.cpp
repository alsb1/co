#include <iostream>
#include <fstream>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

#define UP 0
#define LEFT 1
#define LEFT_UP 2

void print_lcs(int** b, string x, int i, int j) {
    if(i == 0 || j == 0) return ;
    if(b[i][j] == LEFT_UP) {
        print_lcs(b, x, i-1, j-1);
        output << x[i-1];
    }
    else if(b[i][j] == UP)
        print_lcs(b, x, i-1, j);
    else print_lcs(b, x, i, j-1);
}

int** lcs(string x, string y) {
    int n = x.length();
    int m = y.length();

    int** c = new int*[n+1];
    int** b = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        c[i] = new int[m+1];
        b[i] = new int[m+1];
    }

    for(int i = 1; i <= n; i++)
        c[i][0] = 0;
    for(int j = 0; j <= m; j++)
        c[0][j] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(x[i-1] == y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = LEFT_UP;
            }
            else if(c[i-1][j] > c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = UP;
            }
            else {
                c[i][j] = c[i][j-1];
                b[i][j] = LEFT;
            }
        }
    }
    print_lcs(b, x, n, m);
    //cout << c[n][m] << endl;
    return c;
}

void metodo() {
    int n, m;
    string x, y;
    input >> n >> m >> x >> y;
    lcs(x,y);
    output << endl;
}

int main() {
    for(int i = 0; i < 100; i++) 
        metodo();
}
