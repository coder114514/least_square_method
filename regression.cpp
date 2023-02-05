#include<bits/stdc++.h>
using namespace std;

vector<double> x, y;
int n, m;

struct Matrix {
    int n, m;
    vector<vector<double>> data;
    Matrix(int n, int m) : n(n), m(m) {
        data.resize(n+1);
        for (int i = 1; i <= n; i++) {
            data[i].resize(m+1);
        }
    }
    const vector<double>& operator[](int i) const {
        return data[i];
    }
    vector<double>& operator[](int i) {
        return data[i];
    }
    Matrix operator*(const Matrix& o) const {
        if (m != o.n) {
            return Matrix(0, 0);
        }
        Matrix res(n, o.m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= o.m; j++) {
                for (int k = 1; k <= m; k++) {
                    res[i][j] += data[i][k] * o[k][j];
                }
            }
        }
        return res;
    }
};

const double eps = 0.001;

Matrix inv(const Matrix& M) {
    Matrix W(M.m, 2*M.m);
    for (int i = 1; i <= M.m; i++) {
        for (int j = 1; j <= M.m; j++) {
            W[i][j] = M[i][j];
        }
    }
    for (int i = 1; i <= M.m; i++) {
        for (int j = M.m+1; j <= 2*M.m; j++) {
            W[i][j] = (i==j-M.m);
        }
    }
    for (int i = 1; i <= M.m; i++) {
        int r = i;
        for (; r <= M.m; r++) {
            if (fabs(W[r][i]) > eps) {
                break;
            }
        }
        if (r > M.m) {
            return Matrix(0, 0);
        }
        swap(W[r], W[i]);
        for (int k = 1; k <= M.m; k++) {
            if (k == i) {
                continue;
            }
            double ep = W[k][i] / W[i][i];
            for (int j = i; j <= 2*M.m; j++) {
                W[k][j] -= ep*W[i][j];
            }
        }
        double v = W[i][i];
        for (int j = 1; j <= 2*M.m; j++) {
            W[i][j] /= v;
        }
    }
    Matrix res(M.m, M.m);
    for (int i = 1; i <= M.m; i++) {
        for (int j = 1; j <= M.m; j++) {
            res[i][j] = W[i][j+M.m];
        }
    }
    return res;
}

void printPoly(int n, vector<double> a) {
    cout << fixed << setprecision(3);
    while (n >= 0 && fabs(a[n]) < eps) {
        n--;
    }
    if (n < 0) {
        cout << 0;
        return;
    }
    for (int i = n; i >= 0; i--) {
        if (fabs(a[i]) < eps) {
            continue;
        }
        if (a[i] > 0 && i < n) {
            cout << "+";
        }
        if (1-eps > fabs(a[i]) || fabs(a[i]) > 1+eps || i == 0) {
            cout << a[i];
        } else if (-1-eps < a[i] && a[i] < -1+eps) {
            cout << "-";
        }
        if (i > 1) {
            cout << "x^" << i;
        } else if (i == 1) {
            cout << "x";
        }
    }
}

int main() {
    cout << "n points, degree m polynomial (n > m)" << endl;
    cin >> n >> m;
    m++;
    if (n < m) {
        cout << "n < m, unsolvable" << endl;
        return -1;
    }
    x.push_back(0);
    y.push_back(0);
    for (int i = 1; i <= n; i++) {
        double _x, _y;
        cin >> _x >> _y;
        x.push_back(_x);
        y.push_back(_y);
    }
    // round L / round a[i] = 0                 i=0-(m-1)
    // =>
    // M[i][j] = sum k=1-n, pow(x[k],i+j-2)     i=1-m, j=1-m
    // R[i][1] = a[i-1]                         i=1-m
    // V[i][1] = sum j=1-n, pow(x[j],i-1)*y[j]  i=1-m
    // M * R = V
    // R = M^-1 * V
    Matrix M(m, m);
    Matrix V(m, 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            for(int k = 1; k <= n; k++) {
                M[i][j] += pow(x[k], i+j-2);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            V[i][1] += pow(x[j], i-1) * y[j];
        }
    }
    Matrix R = inv(M) * V;
    if (R.n == 0) {
        cout << "unsolvable" << endl;
        return -1;
    }
    vector<double> a;
    for (int i = 1; i <= R.n; i++) {
        a.push_back(R[i][1]);
    }
    cout << "y=";
    printPoly(m-1, a);
    return 0;
}
