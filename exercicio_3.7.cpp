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
                for(int j=k; j<m; j++)
                    V[i][j] -= pivot*V[k][j];
            }
        }
    }

    void copy_last_column_from(Matrix& b) {
        for(int i=0; i<m; i++) 
            V[i][n-1] = b.V[i][n-1];
    }

    void solve_L() {
        for(int i=0; i<m; i++) {
            for(int j=0; j<i; j++) {
                V[i][n-1] -= V[i][j]*V[j][n-1];
                V[i][j] = 0;
            }
        }
    }

    void solve_U() {
        for(int i=m-1; i>=0; i--) {
            double pivot = V[i][i];
            if (abs(pivot) < 1e-6) break;
            for(int j=i; j<n; j++) {
                V[i][j] /= pivot;
            }

            for(int j=i+1; j<n-1; j++) {
                V[i][n-1] -= V[i][j]*V[j][n-1];
                V[i][j] = 0;
            }
        }
    }
};

int main() {
    Matrix U, L;
    
    while(U.read()) {
        U.decompose_LU(L);
        L.copy_last_column_from(U);

        cout << "LY = B:" << endl;
        L.write();

        L.solve_L();
        cout << "solved Y:" << endl;
        L.write();

        U.copy_last_column_from(L);

        cout << "UX = Y:" << endl;
        U.write();

        U.solve_U();
        cout << "solved X:" << endl;
        U.write();

        cout << "---" << endl;
    }
}
