#include <iostream>
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

    void multiply(Matrix& a, Matrix& b) {
        m = a.m;
        n = b.n;
        
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                V[i][j] = 0;
                for(int k=0; k<a.m; k++)
                    V[i][j] += a.V[i][k] * b.V[k][j];    
                
            }
        }
    }
};


int main() {
    Matrix a, b, c;
    
    while(a.read() && b.read()) {
        c.multiply(a, b);
        c.write();
        cout << "---" << endl;
    }
}
