# 連結成分の個数をnum配列に保持
class UnionFind:
    def __init__(self, n):
        self.rank = [0] * n
        self.parent = [i for i in range(n)]
        self.num = [1] * n

    def find(self, x):
        if self.parent[x] == x:
            return x
        else:
            self.parent[x] = self.find(self.parent[x])
            return self.parent[x]

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return
        if self.rank[x] < self.rank[y]:
            self.parent[x] = y
            self.num[y] += self.num[x]
        elif self.rank[x] > self.rank[y]:
            self.parent[y] = x
            self.num[x] += self.num[y]
        else:
            self.parent[x] = y
            self.rank[y] += 1
            self.num[y] += self.num[x]

    def size(self, x):
        return self.num[self.find(x)]
