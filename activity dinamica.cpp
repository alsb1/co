#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void sort(int* s, int* f, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(f[i] > f[j]) {
                int tmp = f[i];
                f[i] = f[j];
                f[j] = tmp;
                
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}

int p(int* s, int* f, int j) {
    int k = -1;
    for(int i = 0; i < j; i++) {
        if(f[i] <= s[j])
            k = i;
    }
    return k;
}

/*
int activity(int* s, int* f, int j){
   if(j == -1) return 0;
   else{
       int a = f[j] - s[j] + activity(s,f,p(s,f,j)), b = activity(s,f,j-1);
        return (a > b ? a : b);
    }
}
*/

int activity(int* s, int* f, int n){
   int* a = new int[n+1];
   a[0] = 0;
   for(int i = 0; i < n; i++) {
       int x = f[i] - s[i] + a[p(s,f,i)+1], y = a[i];
       a[i+1] = (x > y ? x : y);
   }
   return a[n];
}


void metodo(ifstream& input, ofstream& output) {
     int n;
     input >> n;
     int* s = new int[n];
     int* f = new int[n];
     string x;
     for(int i = 0; i < n; i++) {
        input >> x;
        s[i] = atoi(x.substr(1).c_str());
        input >> x;
        f[i] = atoi(x.substr(0, x.length()-1).c_str());
     }
     sort(s, f, n);
     output << activity(s, f, n) << endl; //n-1
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}
