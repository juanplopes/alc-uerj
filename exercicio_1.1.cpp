#include <iostream>
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
    
    bool equals_to(Matrix& b) {
        if (b.m!=m || b.n!=n) 
            return false;
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if (b.V[i][j] != V[i][j])
                    return false;
        return true;        
    }

};

int main() {
    Matrix a, b;
    
    while(a.read() && b.read()) {
        cout << (a.equals_to(b) ? 'T' : 'F') << endl;
    }
}
