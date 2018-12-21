# 二次元ベクトルa, bの外積 = |a||b|sin = ax*by - ay*bx
# 線分a0(x0, y0) a1(x1, y1) と, 線分b0(x2, y2) b1(x3, y3)の交差判定
def cross_judge(x0, y0, x1, y1, x2, y2, x3, y3):
    # a0a1 と a0b0との外積
    ax = x1 - x0
    ay = y1 - y0
    bx = x2 - x0
    by = y2 - y0
    cross_product0 = ax * by - ay * bx

    # a0a1 と a0b1との外積
    ax = x1 - x0
    ay = y1 - y0
    bx = x3 - x0
    by = y3 - y0
    cross_product1 = ax * by - ay * bx

    # b0b1 と b0a0との外積
    ax = x3 - x2
    ay = y3 - y2
    bx = x2 - x0
    by = y2 - y0
    cross_product2 = ax * by - ay * bx

    # b0b1 と b0a1との外積
    ax = x3 - x2
    ay = y3 - y2
    bx = x2 - x1
    by = y2 - y1
    cross_product3 = ax * by - ay * bx

    if cross_product0 * cross_product1 < 0 and cross_product2 * cross_product3 < 0:
        return True
    else:
        return False
