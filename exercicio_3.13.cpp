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

struct Jacobi {
    int n;
    double er;
    double X[MAX], X0[MAX];

    void zero(int newN) {
        n = newN;
        er = 1/0.0;
        for(int i=0; i<n; i++)
            X[i] = X0[i] = 0.0;
    }

    double iterate(Matrix& a) {
        double d = 0, dd = 0;
        for(int i=0; i<n; i++) {
            double sum = 0;
            for(int j=0; j<n; j++)
                if (j!=i)
                    sum+=a.V[i][j]*X0[j];

            X[i] = 1/a.V[i][i]*(a.V[i][n]-sum);

            d = max(d, abs(X[i]-X0[i]));
            dd = max(dd, abs(X[i]));
        }
        for(int i=0; i<n; i++)
            X0[i] = X[i];
        er = d/dd;
        return er;
    }

    void solve(Matrix& a, double err, int maxIter) {
        zero(a.m);
        for(int i=0; i<maxIter; i++) {
            double currentErr = iterate(a);
            cout << fixed << setprecision(6) <<"Iteration #" << (i+1) << ". Epsilon=" << currentErr << endl;
            for(int i=0; i<n; i++)
                cout << (i>0?" ":"") << X[i];
            cout << endl << endl;

            if (currentErr < err)
                break;
        }
    }
};

int main() {
    Matrix A;
    Jacobi J;
    
    while(A.read()) {
        J.solve(A, 1e-3, 20);

        cout << "---" << endl;
    }
}
