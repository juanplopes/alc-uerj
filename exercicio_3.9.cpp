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
    
    void identity(int newM) {
        m = newM;
        n = newM;
        for(int i=0; i<newM; i++)
            for(int j=0; j<newM; j++)
                V[i][j] = i==j;
    }

    void write() {
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++)
                cout << setprecision(4) << fixed << (j>0 ? " " : "") << V[i][j];
            cout <<  endl;
        }
    }

    void decompose_LDLt(Matrix& b) {
        b.m = m;
        b.n = n;
        for(int k=0; k<m; k++) {
            b.V[k][k] = 1;
            for(int i=k+1; i<m; i++) {
                double pivot = V[i][k] / V[k][k];
                b.V[i][k] = pivot;                
                for(int j=k; j<m; j++)
                    V[i][j] -= pivot*V[k][j];
            }
        }
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if (i!=j)
                    V[i][j] = 0;
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
    Matrix L, D, Lt;
    
    while(D.read()) {
        D.decompose_LDLt(L);
        Lt.transpose(L);
        
        cout << "L:" << endl;
        L.write();

        cout << "D:" << endl;
        D.write();

        cout << "Lt:" << endl;
        Lt.write();

        cout << "---" << endl;
    }
}
