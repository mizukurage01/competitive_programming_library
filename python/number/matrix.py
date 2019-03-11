# 行列A, Bの積
def matmul(A, B):
    C = [[0] * len(B[0]) for _ in range(len(A))]
    for i in range(len(A)):
        for k in range(len(B)):
            for j in range(len(B[0])):
                C[i][j] += A[i][k] * B[k][j]
    return C

# 行列Aのn乗
def matpow(A, n):
    B = [[0] * len(A[0]) for _ in range(len(A))]
    for i in range(len(A)):
        B[i][i] = 1
    while n:
        if n & 1:
            B = matmul(B, A)
        A = matmul(A, A)
        n >>= 1
    return B
