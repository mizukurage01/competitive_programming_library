# verified by AOJ Single Source Shortest Path 1

# import heapq
import heapq

# graph: 隣接リスト (頂点、距離）の順に格納
# start: 始点 (0-index)
# n: 頂点数
# memo[t]: startからtまでの最短距離
# return memo

def dijkstra(graph, start, n):
    INF = float('inf')
    memo = [INF] * n
    memo[start] = 0
    q = [(0, start)]

    while q:
        dist, ver = heapq.heappop(q)
        if memo[ver] < dist:
            continue
        for next_ver, next_dist in graph[ver]:
            if memo[next_ver] > dist + next_dist:
                memo[next_ver] = dist + next_dist
                heapq.heappush(q, (dist + next_dist, next_ver))

    return memo
