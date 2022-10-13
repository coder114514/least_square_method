class Matrix:
    def __init__(self, n, m):
        self.n = n
        self.m = m
        self.data = [[0 for i in range(0, m+1)] for i in range(0, n+1)]
    def __mul__(a, b):
        res = Matrix(a.n, b.m)
        for i in range(1, a.n+1):
            for j in range(1, b.m+1):
                for k in range(1, a.m+1):
                    res.data[i][j] += a.data[i][k] * b.data[k][j]
        return res

eps = 0.001

def inv(M):
    W = Matrix(M.m, 2*M.m)
    for i in range(1, M.m+1):
        for j in range(1, M.m+1):
            W.data[i][j] = M.data[i][j]
    for i in range(1, M.m+1):
        for j in range(M.m+1, 2*M.m+1):
            W.data[i][j] = (i==j-M.m)
    for i in range(1, M.m+1):
        for j in range(i, M.m+1):
            if abs(W.data[j][i]) > eps:
                r = j
                break
        W.data[r], W.data[i] = W.data[i], W.data[r]
        for k in range(1, M.m+1):
            if k == i: continue
            ep = W.data[k][i] / W.data[i][i]
            for j in range(i, 2*M.m+1):
                W.data[k][j] -= ep*W.data[i][j]
        v = W.data[i][i]
        for j in range(1, 2*M.m+1):
            W.data[i][j] /= v
    res = Matrix(M.m, M.m)
    for i in range(1, M.m+1):
        for j in range(1, M.m+1):
            res.data[i][j] = W.data[i][j+M.m]
    return res

if __name__ == '__main__':
    print("n points, degree m polynomial (n > m)")
    line = input()
    n = int(line.split(' ')[0])
    m = int(line.split(' ')[1])+1
    if n < m:
        print("warning: unsolvable")
        exit(-1)
    x = [0]
    y = [0]
    for i in range(n):
        line = input()
        x.append(int(line.split(' ')[0]))
        y.append(int(line.split(' ')[1]))
    # round L / round a[i] = 0                 i=0-(m-1)
    # =>
    # M[i][j] = sum k=1-n, pow(x[k],i+j-2)     i=1-m, j=1-m
    # R[i][1] = a[i-1]                         i=1-m
    # V[i][1] = sum j=1-n, pow(x[j],i-1)*y[j]  i=1-m
    # M * R = V
    # R = M^-1 * V
    M = Matrix(m, m)
    V = Matrix(m, 1)
    for i in range(1, m+1):
        for j in range(1, m+1):
            for k in range(1, n+1):
                M.data[i][j] += x[k]**(i+j-2)
    for i in range(1, m+1):
        for j in range(1, n+1):
            V.data[i][1] += (x[j]**(i-1))*y[j]
    R = inv(M) * V
    for i in range(1, m+1):
        print(R.data[i][1], "x^"+str(i-1))
