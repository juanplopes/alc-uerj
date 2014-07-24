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

    void swap_lines(int a, int b) {
        for(int j=0; j<n; j++)
            swap(V[a][j], V[b][j]);
    }

    void decompose_LU(Matrix& b, Matrix& p) {
        b.m = m;
        b.n = n;
        for(int k=0; k<m; k++) {
            int best = k;
            for(int i=k+1; i<m; i++)
                if (abs(V[i][k]) > abs(V[best][k]))
                    best = i;

            swap_lines(best, k);
            p.swap_lines(best, k);
            b.swap_lines(best, k);

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
    Matrix U, L, P;
    
    while(U.read()) {
        P.identity(U.m);

        U.decompose_LU(L, P);
        cout << "P:" << endl;
        P.write();

        L.copy_last_column_from(U);

        cout << "LY = PB:" << endl;
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
