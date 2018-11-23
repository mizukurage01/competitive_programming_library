def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

---
def lcm(a, b):
    g = gcd(a, b)
    g_a = a // g
    g_b = b // g
    return g_a * g_b * g

---
# ax + by = gcd(a, b)
# 返り値: (gcd(a, b), x, y )
def ex_euclid(a, b):
    r0, r1 = a, b
    x0, y0 = 1, 0
    x1, y1 = 0, 1

    while r1 != 0:
        m = r0 % r1
        q = r0 // r1

        r0, r1 = r1, m
        x0, x1 = x1, (x0 - q * x1)
        y0, y1 = y1, (y0 - q * y1)

    return r0, x0, y0
