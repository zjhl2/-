#include <bits/stdc++.h>
 
using namespace std;
 
#define rep(i, a, b)    for (int i(a); i <= (b); ++i)
#define dec(i, a, b)    for (int i(a); i >= (b); --i)
#define MP      make_pair
#define fi      first
#define se      second
 
 
typedef long long LL;
 
const int N = 1e5 + 10;
const int M = 1e7 + 10;
 
int n, m, cnt, tot, ans;
int a[N], b[N], sz[N];
int root[N];
int s[M], ls[M], rs[M];
int son[N], deep[N], top[N], father[N];
vector <int> v[N];
 
 
void build(int &rt, int l, int r){
    rt = ++tot;
    s[rt] = 0;
    if (l >= r) return;
    int mid = (l + r) >> 1;
    build(ls[rt], l, mid);
    build(rs[rt], mid + 1, r);
}
 
 
void update(int &x, int y, int l, int r, int pos){
    x = ++tot;
    ls[x] = ls[y];
    rs[x] = rs[y];
    s[x] = s[y] + 1;
 
    if (l >= r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(ls[x], ls[y], l, mid, pos);
    else update(rs[x], rs[y], mid + 1, r, pos);
}
 
int query(int l, int r, int x1, int x2, int x3, int x4, int k){
    if (l >= r) return l;
    int mid = (l + r) >> 1;
    int now = s[ls[x1]] + s[ls[x2]] - s[ls[x3]] - s[ls[x4]];
    if (k <= now) return query(l, mid, ls[x1], ls[x2], ls[x3], ls[x4], k);
    else return query(mid + 1, r, rs[x1], rs[x2], rs[x3], rs[x4], k - now);
}
 
void dfs(int x, int fa, int dep){
    deep[x] = dep;
    father[x] = fa;
    sz[x] = 1;
    son[x] = 0;
 
    update(root[x], root[father[x]], 1, cnt, a[x]);
 
    int et = (int)v[x].size();
    rep(i, 0, et - 1){
        int u = v[x][i];
        if (u == fa) continue;
        dfs(u, x, dep + 1);
        sz[x] += sz[u];
        if (sz[son[x]] < sz[u]) son[x] = u;
    }
}
 
void dfs2(int x, int tp){
    top[x] = tp;
    if (son[x]) dfs2(son[x], tp);
    int et = (int)v[x].size();
    rep(i, 0, et - 1){
        int u = v[x][i];
        if (u == son[x] || u == father[x]) continue;
        dfs2(u, u);
    }
}
 
int lca(int x, int y){
    int fx = top[x], fy = top[y];
    while (fx ^ fy){
        if (deep[fx] < deep[fy]) swap(x, y), swap(fx, fy);
        x = father[fx], fx = top[x];
    }
    if (deep[x] > deep[y]) swap(x, y);
    return x;
}
 
int main(){
 
    scanf("%d%d", &n, &m);
    rep(i, 1, n){
        scanf("%d", a + i);
        b[i] = a[i];
    }
 
    rep(i, 2, n){
        int x, y;
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
 
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, n) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
 
    build(root[0], 1, cnt);
 
    dfs(1, 0, 1);
    dfs2(1, 1);
 
    ans = 0;
    while (m--){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x ^= ans;
        int u = lca(x, y);
        int fu = father[u];
        printf("%d", ans = b[query(1, cnt, root[x], root[y], root[u], root[fu], z)]);
        if (m) putchar(10);
    }
 
    return 0;
}

Z-Will 2018/7/9 22:45:51
