#include <iostream>
#include <iomanip>
#include <cmath>
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
                cout << setprecision(4) << fixed << (j>0 ? " " : "") << V[i][j];
            cout <<  endl;
        }
    }

    void decompose_LU(Matrix& b) {
        b.m = m;
        b.n = n;
        for(int k=0; k<m; k++) {
            b.V[k][k] = 1;
            for(int i=k+1; i<m; i++) {
                double pivot = V[i][k] / V[k][k];
                b.V[i][k] = pivot;                
                for(int j=k; j<n; j++)
                    V[i][j] -= pivot*V[k][j];
            }
        }
    }
};

int main() {
    Matrix U, L;
    
    while(U.read()) {
        U.decompose_LU(L);
        cout << "L:" << endl;
        L.write();
        cout << "U:" << endl;
        U.write();
        cout << "---" << endl;
    }
}
