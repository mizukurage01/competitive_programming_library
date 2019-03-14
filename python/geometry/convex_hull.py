# ベクトルp0p1に対する点p2の位置（反時計回り, もしくは直線上ならTrue, 時計回りならFalse）を返す。
def ccw(p0, p1, p2):
    return (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p1[1] - p0[1]) * (p2[0] - p0[0]) >= 0   # (ベクトルp0p1とベクトルp0p2の外積) >= 0

# 凸包を求める。psは点(x, y)の集合。
def convex_hull(ps):
    upper = []
    lower = []
    ps.sort()
    for p in ps:
        while len(lower) > 1 and ccw(lower[-2], lower[-1], p):
            lower.pop()
        lower.append(p)

    for p in ps[::-1]:
        while len(upper) > 1 and ccw(upper[-2], upper[-1], p):
            upper.pop()
        upper.append(p)
    return lower[:-1] + upper[:-1]
