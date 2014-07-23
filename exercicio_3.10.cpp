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

            for(int i=k+1; i<n; i++) {
                sum = 0;
                for(int j=0; j<k; j++) {
                    sum += V[i][j]*V[k][j];
                }
                V[i][k] = (a.V[i][k] - sum) / V[k][k];
            }
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
    Matrix A, G;
    
    while(A.read()) {
        G.decompose_cholesky(A);
        G.write();
        cout << "---" << endl;
    }
}
