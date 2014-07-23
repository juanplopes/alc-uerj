#include <iostream>
#include <string>
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
    
    void add(Matrix& a, Matrix& b) {
        m = a.m;
        n = a.n;
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                V[i][j] = a.V[i][j] + b.V[i][j];
    }

    void sub(Matrix& a, Matrix& b) {
        m = a.m;
        n = a.n;
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                V[i][j] = a.V[i][j] - b.V[i][j];
    }

    void mul(Matrix& a, double scalar) {
        m = a.m;
        n = a.n;
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                V[i][j] = a.V[i][j] * scalar;
    }
};


int main() {
    string command;
    Matrix a, b, c;
    
    while(cin >> command) {
        if (command == "add") {
            a.read(); b.read();
            c.add(a, b);
        }
        
        if (command == "sub") {
            a.read(); b.read();
            c.sub(a, b);
        }
    
        if (command == "mul") {
            a.read();
            double scalar; cin >> scalar;
            c.mul(a, scalar);
        }
        c.write();
        cout << "---" << endl;
    }
}
