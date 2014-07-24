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
};

struct PowerIteration {
    int n, p;
    double X[MAX], Y[MAX], err, mi;

    void zero(int newN) {
        n = newN;
        p = 0;
        err = 1/0.0;
        mi = 0;
        for(int i=0; i<n; i++)
            X[i] = 1.0;
    }

    bool iterate(Matrix& a, double maxErr) {
        int maxx = 0;
        for(int i=0; i<n; i++) {
            Y[i] = 0;
            for(int j=0; j<n; j++)
                Y[i] += a.V[i][j] * X[j];
            if (abs(Y[i]) > abs(Y[maxx])) 
                maxx = i;
        }
        mi = Y[p];
        p = maxx;

        err = 0;
        for(int i=0; i<n; i++)
            err = max(err, abs(X[i] - Y[i]/Y[p]));

        if (err < maxErr)
            return true;

        for(int i=0; i<n; i++)
            X[i] = Y[i]/Y[p];
    }

    void solve(Matrix& a, double maxErr, int maxIter) {
        zero(a.m);
        for(int i=0; i<maxIter; i++) {
            iterate(a, maxErr);
            cout << fixed << setprecision(6) <<"Iteration #" << (i+1) << ". Epsilon=" << err << endl;
            cout << "Eigenvalue: " << mi << endl;
            cout << "Eigenvector:" << endl;
            for(int i=0; i<n; i++)
                cout << (i>0?" ":"") << X[i];
            cout << endl << endl;

            if (err < maxErr)
                break;
        }
    }
};

int main() {
    Matrix A;
    PowerIteration P;
    
    while(A.read()) {
        P.solve(A, 1e-4, 20);

        cout << "---" << endl;
    }
}
