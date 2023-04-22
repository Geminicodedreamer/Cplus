#include <bits/stdc++.h>
/*
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <map>
#include <vector>
*/
// #define double long double
//  #define x first
//  #define y second

using namespace std;

const int N = 100010;
const double eps = 1e-12; // 精度
const double PI = acos(-1);
const double INF = 1e8;

typedef pair<int, int> PII;
typedef pair<double, double> PDD;

struct Point
{ // 坐标(也是向量)
    double x, y;
    Point() {}
    Point(double x, double y)
    {
        this->x = x, this->y = y;
    }
    friend istream &operator>>(istream &input, Point &range)
    {
        input >> range.x >> range.y;
        return input;
    }
    friend ostream &operator<<(ostream &output, Point &range)
    {
        output << range.x << ' ' << range.y << '\n';
        return output;
    }
    bool operator==(const Point &range) const
    {
        return range.x == x && range.y == y;
    }
    bool operator<(const Point &a) const
    {
        if (x == a.x)
            return y < a.y;
        return x < a.x;
    }
    bool operator>(const Point &a) const
    {
        if (x == a.x)
            return y > a.y;
        return x > a.x;
    }
};

// Point 的运算符重载
Point operator-(Point a, Point b)
{
    return {a.x - b.x, a.y - b.y};
}

Point operator+(Point a, Point b)
{
    return {a.x + b.x, a.y + b.y};
}
// 数量积
Point operator*(Point a, double t)
{
    return {a.x * t, a.y * t};
}

Point operator/(Point a, double t)
{
    return {a.x / t, a.y / t};
}
// 外积(叉积)
double operator*(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}
// 内积(点积)
double operator&(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

struct Line
{
    Point st, ed;
    vector<int> ids; // 共线
};

struct Circle
{
    Point O;
    double r;
    Circle() {}
    Circle(Point O, double r)
    {
        this->O = O, this->r = r;
    }
};

// 比较函数
int dcmp(double x, double y)
{
    if (fabs(x - y) < eps)
        return 0;
    if (x < y)
        return -1;
    return 1;
}

// 符号函数
int sign(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    return 1;
}

// 取模
double get_length(Point a)
{
    return sqrt(a & a);
}

// 计算线段长度
double get_dist(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 计算向量夹角
double get_angle(Point a, Point b)
{
    return acos((a & b) / get_length(a) / get_length(b));
}

// 求直线倾角
double get_angle(const Line &a)
{
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

// 计算两个向量构成的三角形的有向面积
double area(Point a, Point b, Point c)
{
    return (b - a) * (c - a) / 2;
}

// 求单位向量
Point norm(Point a)
{
    return a / get_length(a);
}

// 向量A顺时针旋转C的角度
Point rotate(Point a, double angle)
{
    return Point(a.x * cos(angle) + a.y * sin(angle), -a.x * sin(angle) + a.y * cos(angle));
}

// 两直线相交交点(不含平行的情况) 跨立实验 返回INF表示两直线平行
Point get_line_intersection(Point p, Point v, Point q, Point w)
{
    if (!sign(v * w))
        return {INF, INF};
    Point u = p - q;
    double t = (w * u) / (w * v);
    v = v * t;
    return v + p;
}

// 直线交点 (直线版重载)
Point get_line_intersection(Line a, Line b)
{
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

// 点是否在线段上
bool on_segment(Point p, Point a, Point b)
{
    return sign((p - a) * (p - b)) == 0 && sign((p - a) & (p - b)) <= 0;
}

// 线段交点
Point get_segment_intersection(Point p, Point v, Point q, Point w)
{
    if (!sign(v * w))
        return {INF, INF};
    auto u = p - q;
    auto t = w * u / (v * w);
    auto o = p + v * t;
    if (!on_segment(o, p, p + v) || !on_segment(o, q, q + w))
        return {INF, INF};
    return o;
}

// 求点在直线上投影的长度
double project(Point a, Point b, Point c)
{
    return ((b - a) & (c - a)) / get_length(b - a);
}

// 点到直线的距离
double distance_to_line(Point p, Point a, Point b)
{
    Point v1 = b - a, v2 = p - a;
    return fabs(v1 * v2 / get_length(v1));
}

// 点到线段的距离
double distance_to_segment(Point p, Point a, Point b)
{
    if (a == b)
        return get_length(p - a);
    Point v1 = b - a, v2 = p - a, v3 = p - b;
    if (sign(v1 & v2) < 0)
        return get_length(v2);
    if (sign(v1 & v3) > 0)
        return get_length(v3);
    return distance_to_line(p, a, b);
}

// 点在直线上的投影
Point get_line_projection(Point p, Point a, Point b)
{
    Point v = b - a;
    v = v * ((v & (p - a)) / get_length(v));
    return a + v;
}

// 判断两线段是否相交
bool segment_intersection(Point a1, Point a2, Point b1, Point b2)
{
    if (min(a1.x, a2.x) <= max(b1.x, b2.x) && min(b1.x, b2.x) <= max(a1.x, a2.x) && min(a1.y, a2.y) <= max(b1.y, b2.y) && min(b1.y, b2.y) <= max(a1.y, a2.y))
    {
        double c1 = (a2 - a1) * (b1 - a1), c2 = (a2 - a1) * (b2 - a1);
        double c3 = (b2 - b1) * (a2 - b1), c4 = (b2 - b1) * (a1 - b1);
        return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
    }
    else
        return false;
}

// 海伦公式
double heron(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    return S;
}

// 求多边形面积（不一定是凸多边形）
// 我们可以从第一个顶点除法把凸多边形分成n − 2个三角形，然后把面积加起来。
double polygon_area(Point p[], int n)
{
    double s = 0;
    for (int i = 1; i + 1 < n; i++)
        s += (p[i] - p[0]) * (p[i + 1] - p[i]);
    return fabs(s / 2);
}

// 求圆的面积
double circle_area(Circle o)
{
    return PI * o.r * o.r;
}

// 皮克定理
double pick_area(int a, int b) // 适用于求顶点在格点上的多边形面积
{
    return (double)(a + (b / 2.0) - 1.0); // a 是多边形内部的整点个数, b 是边上的整点个数
}

// 绕线段a端点顺时针旋转x度(角度制)对应坐标 向量乘以矩阵
Point spin(Point a, Point b, double jiao)
{
    double theta = PI * jiao / 180.0; // jiao度转成弧度
    Point res;
    res.x = cos(theta) * (b.x - a.x) - sin(theta) * (b.y - a.y) + a.x;
    res.y = sin(theta) * (b.x - a.x) + cos(theta) * (b.y - a.y) + a.y;
    return res;
}

// 安德鲁凸包算法(求逆时针点坐标,包括边界上的坐标)
int stk[N], top = 0;
bool used[N];
void andrew_id(int n, Point q[])
{
    sort(q, q + n);
    for (int i = 0; i < n; i++) // 先求下凸壳
    {
        while (top >= 2 && sign(area(q[stk[top - 1]], q[stk[top]], q[i])) > 0)
        {
            used[stk[top]] = false;
            top--;
        }
        stk[++top] = i;
        used[i] = true;
    }
    used[0] = 0;
    for (int i = n - 1; i >= 0; i--) // 再求上凸壳
    {
        if (used[i])
            continue;
        while (top >= 2 && sign(area(q[stk[top - 1]], q[stk[top]], q[i])) > 0)
            top--;
        stk[++top] = i;
    }
    top--;

    printf("%d\n", top);
    for (int i = 1; i <= top; i++)
        cout << q[stk[i]];
}

// 安德鲁凸包算法(求周长)
double andrew_C(int n, Point q[]) // 顺时针存点
{
    sort(q, q + n);
    int top = 0;
    for (int i = 0; i < n; i++) // 先求上凸壳
    {
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
        {
            // 凸包边界上的点即使被从栈中删掉，也不能删掉used上的标记
            if (area(q[stk[top - 1]], q[stk[top]], q[i]) < 0)
                used[stk[top--]] = false;
            else
                top--;
        }
        stk[++top] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) // 再求下凸壳
    {
        if (used[i])
            continue;
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
            top--;
        stk[++top] = i;
    }

    double res = 0;
    for (int i = 2; i <= top; i++)
        res += get_dist(q[stk[i - 1]], q[stk[i]]);
    return res;
}

// 半平面交
// 1.对斜率进行排序
bool cmp(const Line &a, const Line &b)
{
    double A = get_angle(a), B = get_angle(b);
    if (!dcmp(A, B))
        return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}
// 2.看焦点确定是否更新 // bc的交点是否在a的右侧
bool on_right(Line &a, Line &b, Line &c)
{
    auto o = get_line_intersection(b, c);
    return sign(area(a.st, a.ed, o)) <= 0;
}

// 半平面交主体(求面积版)
Line line[N];
int q[N];
Point pg[N];
double half_plane_intersection_area(int n)
{
    Point ans[N];
    int cnt = 0;
    int m;
    while (n--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%lf%lf", &pg[i].x, &pg[i].y);
        for (int i = 0; i < m; i++)
            line[cnt++] = {pg[i], pg[(i + 1) % m]};
    }

    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1; // 双端队列
    for (int i = 0; i < cnt; i++)
    {
        if (i && !dcmp(get_angle(line[i]), get_angle(line[i - 1])))
            continue;
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]]))
            tt--;
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]]))
            hh++;
        q[++tt] = i;
    }
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]]))
        tt--;
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]]))
        hh++;

    q[++tt] = q[hh];
    int k = 0;
    for (int i = hh; i < tt; i++)
        ans[k++] = get_line_intersection(line[q[i]], line[q[i + 1]]);
    double res = 0;
    for (int i = 1; i + 1 < k; i++)
        res += area(ans[0], ans[i], ans[i + 1]);
    return res / 2;
}

// 半平面交(求轮廓边id版)
double ki[N], vi[N];
void half_plane_intersection_id(int n)
{
    int ans[N];
    int cnt = 0;
    map<Point, vector<int>> ids;
    for (int i = 1; i <= n; i++)
        scanf("%lf", &ki[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &vi[i]);
    for (int i = 1; i <= n; i++)
        ids[{ki[i], vi[i]}].push_back(i);

    line[cnt++] = {{0, 10000}, {0, 0}};
    line[cnt++] = {{0, 0}, {10000, 0}};
    for (auto &[k, v] : ids)
        line[cnt++] = {{0, k.x}, {1, k.x + k.y}, v};
    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1;
    for (int i = 0; i < cnt; i++)
    {
        if (i && !dcmp(get_angle(line[i - 1]), get_angle(line[i])))
            continue;
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]]))
            tt--;
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]]))
            hh++;
        q[++tt] = i;
    }
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]]))
        tt--;
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]]))
        hh++;

    int k = 0;
    for (int i = hh; i <= tt; i++)
        for (auto id : line[q[i]].ids)
            ans[k++] = id;
    sort(ans, ans + k);

    printf("%d\n", k);
    for (int i = 0; i < k; i++)
        printf("%d ", ans[i]);
    puts("");
}

// 判断点和多边形的关系(内 2,外 0,上 1)
int PtInPolygon(Point p, Point ptPolygon[], int n)
{
    bool ju = true;
    int nCross = 0; // 交点个数
    for (int i = 0; i < n; i++)
    {
        Point p1 = ptPolygon[i];
        Point p2 = ptPolygon[(i + 1) % n]; // 点P1与P2形成连线
        if (on_segment(p, p1, p2))         // 点是否在线段上
        {
            ju = false;
            break;
        }
        if (p1.y == p2.y)
            continue;
        if (p.y < min(p1.y, p2.y))
            continue;
        if (p.y >= max(p1.y, p2.y))
            continue;

        // 求交点的x坐标（由直线两点式方程转化而来）

        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

        // 只统计p1p2与p向右射线的交点
        if (x > p.x)
        {
            nCross++;
        }
    }

    // 交点为偶数，点在多边形之外
    // 交点为奇数，点在多边形之内
    if (ju)
        if ((nCross % 2) == 1)
            return 2;
        else
            return 0;
    else
        return 1;
}

// 最小圆覆盖
// 1.求中垂线
pair<Point, Point> get_line(Point a, Point b)
{
    return {(a + b) / 2, rotate(b - a, PI / 2)};
}
// 2.三点确定一个圆
Circle get_circle(Point a, Point b, Point c)
{
    pair<Point, Point> u = get_line(a, b), v = get_line(a, c);
    Point p = get_line_intersection(u.first, u.second, v.first, v.second);
    return {p, get_dist(p, a)};
}
// O(n)求最小圆覆盖
void get_min_circle_cover(int n, Point p[])
{
    random_shuffle(p, p + n);

    Circle c({p[0], 0});
    for (int i = 1; i < n; i++)
        if (dcmp(c.r, get_dist(c.O, p[i])) < 0)
        {
            c = {p[i], 0};
            for (int j = 0; j < i; j++)
                if (dcmp(c.r, get_dist(c.O, p[j])) < 0)
                {
                    c = {(p[i] + p[j]) / 2, get_dist(p[i], p[j]) / 2.0};
                    for (int k = 0; k < j; k++)
                        if (dcmp(c.r, get_dist(c.O, p[k])) < 0)
                            c = get_circle(p[i], p[j], p[k]);
                }
        }

    printf("%f\n", c.r);
    printf("%f %f\n", c.O.x, c.O.y);
}
// 拓展:最小覆盖椭圆(已知a / b = p和横轴倾角a) 求椭圆长轴
void get_min_elliptical(Point q[], double p, int n, double a)
{
    for (int i = 0; i < n; i++)
    {
        q[i] = rotate(q[i], a / 180 * PI);
        q[i].x /= p;
    }
    random_shuffle(q, q + n);
    Circle c({q[0], 0});
    for (int i = 1; i < n; i++)
        if (dcmp(c.r, get_dist(c.O, q[i])) < 0)
        {
            c = {q[i], 0};
            for (int j = 0; j < i; j++)
                if (dcmp(c.r, get_dist(c.O, q[j])) < 0)
                {
                    c = {(q[i] + q[j]) / 2, get_dist(q[i], q[j]) / 2};
                    for (int k = 0; k < j; k++)
                        if (dcmp(c.r, get_dist(c.O, q[k])) < 0)
                            c = get_circle(q[i], q[j], q[k]);
                }
        }

    printf("%.3lf\n", c.r);
}

// 旋转卡壳

// 1.凸包直径(点集中两点的最远距离)
// 先求出凸包(安德鲁)再旋转卡壳
double rotating_calipers(int n, Point q[])
{
    sort(q, q + n);
    for (int i = 0; i < n; i++)
    {
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
        {
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[--top]] = false;
            else
                top--;
        }
        stk[top++] = i;
        used[i] = true;
    }

    used[0] = false;
    for (int i = n - 1; i >= 0; i--)
    {
        if (used[i])
            continue;
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top--;
        stk[top++] = i;
    }
    top--;
    if (top <= 2)
        return get_dist(q[0], q[n - 1]);

    double res = 0;
    for (int i = 0, j = 2; i < top; i++)
    {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[j + 1]]))
            j = (j + 1) % top;
        res = max(res, max(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]])));
    }
    return res;
}

// 2.最小矩形覆盖(精度必须低一点1e-8)
// 先求凸包再枚举每条边当矩形的边求其面积和坐标
// 先输出 y坐标最小的顶点的 x,y坐标，如果有两个点的 y坐标同时达到最小，则先输出 x坐标较小者的 x,y坐标。
Point ans[N];
double min_area = INF;
void get_min_rectangle(int n, Point q[])
{
    sort(q, q + n);
    for (int i = 0; i < n; i++)
    {
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            used[stk[--top]] = false;
        stk[top++] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i--)
    {
        if (used[i])
            continue;
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            top--;
        stk[top++] = i;
    }
    reverse(stk, stk + top);
    top--;
    for (int i = 0, a = 2, b = 1, c = 2; i < top; i++)
    {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (dcmp(area(d, e, q[stk[a]]), area(d, e, q[stk[a + 1]])) < 0)
            a = (a + 1) % top;
        while (dcmp(project(d, e, q[stk[b]]), project(d, e, q[stk[b + 1]])) < 0)
            b = (b + 1) % top;
        if (!i)
            c = a;
        while (dcmp(project(d, e, q[stk[c]]), project(d, e, q[stk[c + 1]])) > 0)
            c = (c + 1) % top;
        auto x = q[stk[a]], y = q[stk[b]], z = q[stk[c]];
        auto h = area(d, e, x) / get_length(e - d);
        auto w = ((y - z) & (e - d)) / get_length(e - d);
        if (h * w < min_area)
        {
            min_area = h * w;
            ans[0] = d + norm(e - d) * project(d, e, y);
            ans[3] = d + norm(e - d) * project(d, e, z);
            auto u = norm(rotate(e - d, -PI / 2));
            ans[1] = ans[0] + u * h;
            ans[2] = ans[3] + u * h;
        }
    }
    int k = 0;
    for (int i = 1; i < 4; i++)
        if (dcmp(ans[i].y, ans[k].y) < 0 || !dcmp(ans[i].y, ans[k].y) && dcmp(ans[i].x, ans[k].x) < 0)
            k = i;

    printf("%.5lf\n", min_area);
    for (int i = 0; i < 4; i++, k++)
    {
        auto x = ans[k % 4].x, y = ans[k % 4].y;
        if (!sign(x))
            x = 0;
        if (!sign(y))
            y = 0;
        printf("%.5lf %.5lf\n", x, y);
    }
}

// 三角刨分(圆和多边形的面积并)
// 求圆和直线的交点
double get_circle_line_intersection(Point a, Point b, Point &pa, Point &pb, Circle o)
{
    auto e = get_line_intersection(a, b - a, o.O, rotate(b - a, PI / 2));
    auto mind = get_dist(o.O, e);
    if (!on_segment(e, a, b))
        mind = min(get_dist(o.O, a), get_dist(o.O, b));
    if (dcmp(o.r, mind) <= 0)
        return mind;
    auto len = sqrt(o.r * o.r - get_dist(o.O, e) * get_dist(o.O, e));
    pa = e + norm(a - b) * len;
    pb = e + norm(b - a) * len;
    return mind;
}
// 求扇形面积
double get_sector(Point a, Point b, Circle o)
{
    double angle = get_angle(a, b);
    if (sign(a * b) < 0)
        angle = -angle;
    return o.r * o.r * angle / 2;
}
// 求每两个点和圆心连线的三角形和圆的交集面积
double get_circle_triangle_area(Point a, Point b, Circle o)
{
    auto da = get_dist(o.O, a), db = get_dist(o.O, b);
    if (dcmp(o.r, da) >= 0 && dcmp(o.r, db) >= 0)
        return a * b / 2;
    if (!sign(a * b))
        return 0;
    Point pa, pb;
    auto mind = get_circle_line_intersection(a, b, pa, pb, o);
    if (dcmp(o.r, mind) <= 0)
        return get_sector(a, b, o);
    if (dcmp(o.r, da) >= 0)
        return a * pb / 2 + get_sector(pb, b, o);
    if (dcmp(o.r, db) >= 0)
        return get_sector(a, pa, o) + pa * b / 2;
    return get_sector(a, pa, o) + pa * pb / 2 + get_sector(pb, b, o);
}
// 多边形和圆的面积交集(面积交)
double get_Polygon_circle_public_area(int n, Point q[], Circle o)
{
    double res = 0;
    for (int i = 0; i < n; i++)
        res += get_circle_triangle_area(q[i], q[(i + 1) % n], o);
    return fabs(res);
}
// 多边形和圆的面积并集(面积并)
double get_Polygon_circle_total_area(int n, Point q[], Circle o)
{
    return polygon_area(q, n) + circle_area(o) - get_Polygon_circle_public_area(n, q, o);
}

// 扫描线

// 矩形面积并
// 1.数据范围小(区间合并版)
Point l[N], r[N], alls[N];
// 维护每一长条的高的并集并求出该长条的面积
double range_area(int n, double a, double b)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (l[i].x <= a && r[i].x >= b)
            alls[cnt++] = {l[i].y, r[i].y};
    if (!cnt)
        return 0;
    sort(alls, alls + cnt);
    double res = 0;
    double st = alls[0].x, ed = alls[0].y;
    for (int i = 1; i < cnt; i++)
        if (alls[i].x <= ed)
            ed = max(ed, alls[i].y);
        else
        {
            res += ed - st;
            st = alls[i].x, ed = alls[i].y;
        }
    res += ed - st;
    return res * (b - a);
}
double get_retangle_total_area_small(int n)
{
    vector<int> xs;
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf%lf%lf", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
        xs.push_back(l[i].x), xs.push_back(r[i].x);
    }
    sort(xs.begin(), xs.end());
    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i++)
        if (xs[i] != xs[i + 1])
            res += range_area(n, xs[i], xs[i + 1]);
    printf("%f\n", res);
    return res;
}
// 2.数据范围大(线段树版)
struct Segment
{
    double x, y1, y2;
    int k;
    bool operator<(const Segment &t) const
    {
        return x < t.x;
    }
} seg[N * 2];
struct Node
{
    int l, r;
    int cnt;
    double len;
} tr[N * 8];
vector<double> ys;
int find(double y)
{
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}
void pushup(int u)
{
    if (tr[u].cnt)
        tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
    else if (tr[u].l != tr[u].r)
    {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    else
        tr[u].len = 0;
}
void build(int u, int l, int r)
{
    tr[u] = {l, r, 0, 0};
    if (l != r)
    {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }
}
void modify(int u, int l, int r, int k)
{
    if (tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].cnt += k;
        pushup(u);
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid)
            modify(u << 1, l, r, k);
        if (r > mid)
            modify(u << 1 | 1, l, r, k);
        pushup(u);
    }
}
double get_retangle_total_area_huge(int n)
{
    for (int i = 0, j = 0; i < n; i++)
    {
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        seg[j++] = {x1, y1, y2, 1};
        seg[j++] = {x2, y1, y2, -1};
        ys.push_back(y1), ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    build(1, 0, ys.size() - 2);

    sort(seg, seg + n * 2);

    double res = 0;
    for (int i = 0; i < n * 2; i++)
    {
        if (i > 0)
            res += tr[1].len * (seg[i].x - seg[i - 1].x);
        modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
    }
    printf("%.2lf", res);
    return res;
}

// 三角形面积并
// 求扫描线之间的面积
Point tri[N][3];
Point unit[N];
// 求每对扫描线之间的有交集线段的并集
double line_area(int n, double a, int side)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        auto t = tri[i];
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0)
            continue;
        if (!dcmp(t[0].x, a) && !dcmp(t[1].x, a))
        {
            if (side)
                unit[cnt++] = {t[0].y, t[1].y};
        }
        else if (!dcmp(t[2].x, a) && !dcmp(t[1].x, a))
        {
            if (!side)
                unit[cnt++] = {t[2].y, t[1].y};
        }
        else
        {
            double d[3];
            int u = 0;
            for (int j = 0; j < 3; j++)
            {
                auto o = get_line_intersection(t[j], t[(j + 1) % 3] - t[j], {a, -INF}, {0, INF * 2});
                if (dcmp(o.x, INF))
                    d[u++] = o.y;
            }
            if (u)
            {
                sort(d, d + u);
                unit[cnt++] = {d[0], d[u - 1]};
            }
        }
    }
    if (!cnt)
        return 0;
    for (int i = 0; i < cnt; i++)
        if (unit[i].x > unit[i].y)
            swap(unit[i].x, unit[i].y);
    sort(unit, unit + cnt);
    double res = 0, st = unit[0].x, ed = unit[0].y;
    for (int i = 1; i < cnt; i++)
        if (unit[i].x <= ed)
            ed = max(ed, unit[i].y);
        else
        {
            res += ed - st;
            st = unit[i].x, ed = unit[i].y;
        }
    res += ed - st;
    return res;
}
// 求每对扫描线之间的面积
double range_between_area(int n, double a, double b)
{
    return (line_area(n, a, 1) + line_area(n, b, 0)) * (b - a) / 2;
}
// 三角形面积并
double get_triangle_total_area(int n)
{
    vector<double> xs;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%lf%lf", &tri[i][j].x, &tri[i][j].y);
            xs.push_back(tri[i][j].x);
        }
        sort(tri[i], tri[i] + 3);
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                {
                    auto o = get_segment_intersection(tri[i][x], tri[i][(x + 1) % 3] - tri[i][x],
                                                      tri[j][y], tri[j][(y + 1) % 3] - tri[j][y]);
                    if (dcmp(o.x, INF))
                        xs.push_back(o.x);
                }
    sort(xs.begin(), xs.end());
    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i++)
        if (dcmp(xs[i], xs[i + 1]))
            res += range_between_area(n, xs[i], xs[i + 1]);
    printf("%.8lf\n", res);
    return res;
}

// 自适应辛普森积分
// 求圆的面积并
vector<Point> segs;
Circle c[N];
Point qs[N];
double f(double x, int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        auto X = fabs(x - c[i].O.x), R = c[i].r;
        if (dcmp(X, R) < 0)
        {
            auto Y = sqrt(R * R - X * X);
            qs[cnt++] = {c[i].O.y - Y, c[i].O.y + Y};
        }
    }
    if (!cnt)
        return 0;
    sort(qs, qs + cnt);
    double res = 0, st = qs[0].x, ed = qs[0].y;
    for (int i = 1; i < cnt; i++)
        if (qs[i].x <= ed)
            ed = max(ed, qs[i].y);
        else
        {
            res += ed - st;
            st = qs[i].x, ed = qs[i].y;
        }
    return res + ed - st;
}
double simpson(double l, double r, int n)
{
    auto mid = (l + r) / 2;
    return (r - l) * (f(l, n) + 4 * f(mid, n) + f(r, n)) / 6;
}
double asr(double l, double r, double s, int n)
{
    auto mid = (l + r) / 2;
    auto left = simpson(l, mid, n), right = simpson(mid, r, n);
    if (fabs(s - left - right) < eps)
        return left + right;
    return asr(l, mid, left, n) + asr(mid, r, right, n);
}
void merge() // 区间合并
{
    sort(segs.begin(), segs.end());
    vector<Point> new_segs;
    double l = -INF, r = -INF;
    for (auto &seg : segs)
    {
        if (dcmp(seg.x, r) <= 0)
            r = max(r, seg.y);
        else
        {
            if (dcmp(l, -INF))
                new_segs.push_back({l, r});
            l = seg.x, r = seg.y;
        }
    }
    new_segs.push_back({l, r});
    segs = new_segs;
}
double get_circle_total_area()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf%lf", &c[i].O.x, &c[i].O.y, &c[i].r);
        segs.push_back({c[i].O.x - c[i].r, c[i].O.x + c[i].r});
    }

    merge();
    double res = 0;
    for (auto &seg : segs)
        res += asr(seg.x, seg.y, simpson(seg.x, seg.y, n), n);

    printf("%.3lf\n", res);
    return res;
}

Point p[N];
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0) , cout.tie(0);
    // int n;
    // cin >> n;
    // for(int i = 0 ; i < n ; i ++) cin >> p[i];
    system("pause");
    return 0;
}
/*
三维计算几何知识
1. 三维向量表示(x, y, z)
2. 向量加减法、数乘运算，与二维相同
3. 模长 |A| = sqrt(x * x + y * y + z * z)
4. 点积
    (1) 几何意义：A·B = |A| * |B| * cos(C)
    (2) 代数求解：(x1, y1, z1) · (x2, y2, z2) = (x1x2, y1y2, z1z2);
5. 叉积
    (1) 几何意义：AxB = |A| * |B| * sin(C)，方向：右手定则
    (2) 代数求解：AxB = (y1z2 - z1y2, z1x2 - x1z2, x1y2 - x2y1)
6. 如何求平面法向量
    任取平面上两个不共线的向量A、B：AxB
7. 判断点D是否在平面里
    任取平面上两个不共线的向量A、B：先求法向量C = AxB，然后求平面上任意一点到D的向量E与C的点积，判断点积是否为0。
8. 求点D到平面的距离
    任取平面上两个不共线的向量A、B：先求法向量C = AxB。然后求平面上任意一点到D的向量E在C上的投影长度即可。即：E·C / |C|
9. 多面体欧拉定理
    顶点数 - 棱长数 + 表面数 = 2
10. 三维凸包
*/

/*
三维凸包求表面积
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 210;
const double eps = 1e-12;

int n, m;
bool g[N][N];

double rand_eps()
{
    return ((double)rand() / RAND_MAX - 0.5) * eps;
}

struct Point
{
    double x, y, z;
    void shake()
    {
        x += rand_eps(), y += rand_eps(), z += rand_eps();
    }
    Point operator- (Point t)
    {
        return {x - t.x, y - t.y, z - t.z};
    }
    double operator& (Point t)
    {
        return x * t.x + y * t.y + z * t.z;
    }
    Point operator* (Point t)
    {
        return {y * t.z - t.y * z, z * t.x - x * t.z, x * t.y - y * t.x};
    }
    double len()
    {
        return sqrt(x * x + y * y + z * z);
    }
}q[N];
struct Plane
{
    int v[3];
    Point norm()  // 法向量
    {
        return (q[v[1]] - q[v[0]]) * (q[v[2]] - q[v[0]]);
    }
    double area()  // 求面积
    {
        return norm().len() / 2;
    }
    bool above(Point a)
    {
        return ((a - q[v[0]]) & norm()) >= 0;
    }
}plane[N], np[N];

void get_convex_3d()
{
    plane[m ++ ] = {0, 1, 2};
    plane[m ++ ] = {2, 1, 0};
    for (int i = 3; i < n; i ++ )
    {
        int cnt = 0;
        for (int j = 0; j < m; j ++ )
        {
            bool t = plane[j].above(q[i]);
            if (!t) np[cnt ++ ] = plane[j];
            for (int k = 0; k < 3; k ++ )
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
        }
        for (int j = 0; j < m; j ++ )
            for (int k = 0; k < 3; k ++ )
            {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                if (g[a][b] && !g[b][a])
                    np[cnt ++ ] = {a, b, i};
            }
        m = cnt;
        for (int j = 0; j < m; j ++ ) plane[j] = np[j];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
        q[i].shake();
    }
    get_convex_3d();

    double res = 0;
    for (int i = 0; i < m; i ++ )
        res += plane[i].area();
    printf("%lf\n", res);
    return 0;
}

*/
