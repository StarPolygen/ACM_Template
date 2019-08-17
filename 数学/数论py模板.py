
#扩展欧几里得
def exgcd(m, n, x, y):         # mx + ny = gcd(m,n)
    if n == 0:
        x = 1
        y = 0
        return m, x, y
    a1 = b = 1
    a = b1 = 0
    c = m
    d = n
    q = c//d
    r = c % d
    while r:
        c = d
        d = r
        t = a1
        a1 = a
        a = t-q*a
        t = b1
        b1 = b
        b = t-q*b
        q = c//d
        r = c % d
    x = a
    y = b
    return d, x, y
 
 
def CRT(m, r, n):               #中国剩余定理
    if n == 0:
        return 0
    M = m[0]
    R = r[0]
    for i in range(1, n):
        x = y = 0
        d, x, y = exgcd(M, m[i], x, y)
        if (r[i] - R) % d != 0:
            return - 1
        x = (r[i] - R) // d * x % (m[i] // d)
        R += x * M
        M = M // d * m[i]
        R %= M
    return R if R >= 0 else R + M