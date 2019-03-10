# ガウスの消去法 （蟻本の実装参考）
# 正方行列のみ使用可能。解が1つに定まるときだけ解を返す。それ以外はNoneを返す

EPS = 1e-8
def gauss(A, b):
    n = len(A)
    B = [[0] * (n+1) for _ in range(n)]
    for i, Ai in enumerate(A):
        for j, Aij in enumerate(Ai):
            B[i][j] = Aij
    for i, bi in enumerate(b):
        B[i][n] = bi

    for i in range(n):
        pivot = i
        for j in range(i, n):
            if abs(B[j][i]) > abs(B[pivot][i]):
                pivot = j
        B[i], B[pivot] = B[pivot], B[i]

        if abs(B[i][i]) < EPS:
            return None

        for j in range(i+1, n+1):
            B[i][j] /= B[i][i]
        for j in range(n):
            if i != j:
                for k in range(i+1, n+1):
                    B[j][k] -= B[j][i] * B[i][k]

    x = [0] * n
    for i in range(n):
        x[i] = B[i][n]
    return x
