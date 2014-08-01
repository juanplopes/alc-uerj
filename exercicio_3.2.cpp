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
                cout << setprecision(3) << fixed << (j>0 ? " " : "") << V[i][j];
            cout <<  endl;
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
    Matrix a;
    
    while(a.read()) {
        a.solve_U();
        a.write();
        cout << "---" << endl;
    }
}
