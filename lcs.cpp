#include <iostream>
#include <fstream>

using namespace std;

int** lcs(string x, string y) {
    int n = x.length();
    int m = y.length();
    int** c = new int*[n+1];
    for(int i = 0; i <= n; i++) 
        c[i] = new int[m+1];
    
    for(int i = 1; i <= n; i++)
        c[i][0] = 0;
    for(int j = 0; j <= m; j++)
        c[0][j] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            if(x[i-1] == y[j-1])
                c[i][j] = c[i-1][j-1] + 1;
            else if(c[i-1][j] >= c[i][j-1])
                c[i][j] = c[i-1][j];
            else
                c[i][j] = c[i][j-1];
        }
    return c;
}

void metodo(ifstream& input, ofstream& output) {
    int n, m;
    input >> n >> m;
    string x, y;
    input >> x >> y;
    int** c = lcs(x,y);
    output << c[n][m] << endl;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
