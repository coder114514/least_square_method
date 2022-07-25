#include<bits/stdc++.h>
using namespace std;

vector<double> x, y;
int n;

const double eps = 0.001;
void printPoly(int n, double a[])
{
	cout << fixed << setprecision(3);
	while (n >= 0 && fabs(a[n]) < eps) n--;
	if (n < 0)
	{
		cout << 0;
		return;
	}
	for (int i = n; i >= 0; i--)
    {
        if (fabs(a[i]) < eps) continue;
        if (a[i] > 0 && i < n) cout << "+";
        if (1-eps > fabs(a[i]) || fabs(a[i]) > 1+eps || i == 0) cout << a[i];
        else if (-1-eps < a[i] && a[i] < -1+eps) cout << "-";
        if (i > 1) cout << "x^" << i;
        else if (i == 1) cout << "x";
    }
}

int main()
{
	cin >> n;
	x.push_back(0);
	y.push_back(0);
	for(int i = 1, _x, _y; i <= n; i++) cin >> _x >> _y, x.push_back(_x), y.push_back(_y);
	double sx  = 0;
	double sy  = 0;
	double xy  = 0;
	double sqx = 0;
	for(int i = 1; i <= n; i++)
	{
		sx  += x[i];
		sy  += y[i];
		xy  += x[i]*y[i];
		sqx += x[i]*x[i];
	}
	double k = (n*xy-sx*sy) / (n*sqx-sx*sx);
	double b = sy/n - sx/n*k;
	double a[] = {b, k};
	cout << "y=";
	printPoly(1, a);
	return 0;
}
