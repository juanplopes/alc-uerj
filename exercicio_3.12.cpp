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

    void decompose_cholesky(Matrix& a) {
        m = a.m;
        n = a.n;
        for(int k=0; k<m; k++) {
            double sum = 0;
            for(int j=0; j<k; j++)
                sum += V[k][j]*V[k][j];
            
            double r = a.V[k][k] - sum;
            V[k][k] = sqrt(r);

            for(int i=k+1; i<m; i++) {
                sum = 0;
                for(int j=0; j<k; j++) {
                    sum += V[i][j]*V[k][j];
                }
                V[i][k] = (a.V[i][k] - sum) / V[k][k];
            }
        }
    }

    void copy_last_column_from(Matrix& b) {
        for(int i=0; i<m; i++) 
            V[i][n-1] = b.V[i][n-1];
    }

    void transpose2(Matrix& a) {
        //transposing only the square part
        m = a.m;
        n = a.n;
        
        for(int i=0; i<m; i++)
            for(int j=0; j<m; j++)
                V[i][j] = a.V[j][i];
    }

    void solve_L() {
        for(int i=0; i<m; i++) {
            double pivot = V[i][i];
            for(int j=0; j<n; j++) {
                V[i][j] /= pivot;
            }

            for(int j=0; j<i; j++) {
                V[i][n-1] -= V[i][j]*V[j][n-1];
                V[i][j] = 0;
            }
        }
    }

    void solve_U() {
        for(int i=m-1; i>=0; i--) {
            double pivot = V[i][i];
            for(int j=0; j<n; j++) {
                V[i][j] /= pivot;
            }

            for(int j=i+1; j<m; j++) {
                V[i][n-1] -= V[i][j]*V[j][n-1];
                V[i][j] = 0;
            }
        }
    }
};

int main() {
    Matrix A, G, Gt;
    
    while(A.read()) {
        G.decompose_cholesky(A);
        Gt.transpose2(G);
        G.copy_last_column_from(A);

        cout << "GY = B:" << endl;
        G.write();
        G.solve_L();

        cout << "solved Y:" << endl;
        G.write();

        Gt.copy_last_column_from(G);
        cout << "GtX = Y:" << endl;
        Gt.write();
        Gt.solve_U();

        cout << "solved X:" << endl;
        Gt.write();


        cout << "---" << endl;
    }
}
