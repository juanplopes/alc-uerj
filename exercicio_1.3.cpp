#include <iostream>
#include <string>
#define MAX 200
using namespace std;

struct Matrix {
    int m, n;
    double V[MAX][MAX];
    
    bool read() {
        if (not (cin >> m >> n)) 
            return false;

        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                cin >> V[i][j];
        return true;
    }
    
    void write() {
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++)
                cout << (j>0 ? " " : "") << V[i][j];
            cout << endl;
        }
    }

    void transpose(Matrix& a) {
        m = a.n;
        n = a.m;
        
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                V[i][j] = a.V[j][i];
    }

};




int main() {
    Matrix a, c;
    
    while(a.read()) {
        c.transpose(a);
        c.write();
        cout << "---" << endl;
    }
}
