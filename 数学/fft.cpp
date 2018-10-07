#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ldb;
typedef double db;


namespace fft{ 
    const int mod = 998244353;
    const int L = 20, FN = (1<<L);
    int rev[FN];   
    const db pi = acos(-1);
    const db two_pi = pi * 2;
    struct cp {
        db x, y;
        cp() {}
        cp(db _x) : x(_x), y(0) {}
        cp(db _x, db _y) : x(_x), y(_y) {}
        inline cp operator + (const cp &p) const { return cp(x+p.x, y+p.y); }
        inline cp operator - (const cp &p) const { return cp(x-p.x, y-p.y); }
        inline cp operator * (const cp &p) const { return cp(x*p.x-y*p.y, x*p.y+y*p.x); }
        inline cp operator !() const { return cp(x, -y); }
    } nw[FN+1], f[FN], g[FN], h[FN], hh[FN];
    void init() {
        rev[0] = 0; for (int i = 1; i < FN; i ++) rev[i] = (rev[i>>1]>>1)|((i&1)<<(L-1));
        nw[0] = nw[FN] = cp(1,0);
        for (int i = 1; i <= (FN>>1); i ++) nw[i] = cp(cos(i*two_pi/FN), sin(i*two_pi/FN));
        for (int i = (FN>>1)+1; i < FN; i ++) nw[i] = !nw[FN-i];
    }
    void dft(cp *a, int n, int fg) {
        int d = __builtin_ctz(FN / n);
        for (int i = 0; i < n; i ++) if (i < (rev[i]>>d)) swap(a[i], a[rev[i]>>d]);
        for (int size = 2; size <= n; size <<= 1) {
            int step = FN / size; if (fg) step = -step;
            for (int i = 0; i < n; i += size) {
                cp *u = a + i, *v = a + (i+(size>>1)), *w = fg ? nw + FN : nw;
                for (int k = (size>>1); k --; ) {
                    cp tmp = (*v) * (*w);
                    *v = *u - tmp, *u = *u + tmp;
                    u ++, v ++, w += step;
                }
            }
        } 
        if (fg) for (int i = 0; i < n; i ++) a[i].x /= n, a[i].y /= n;
    }
    /// multiply two polynomial nlog(n) time modulo p
    void multiply(int *a, int *b, int *c, int n) {
        for (int i = 0; i < n; i ++) {
            f[i] = cp( (db)(a[i]>>15), (db)(a[i]&32767) );
            g[i] = cp( (db)(b[i]>>15), (db)(b[i]&32767) );
        }
        dft(f, n, 0);
        dft(g, n, 0);
        for (int i = 0; i < n; i ++) {
            int j = i ? n - i : 0;
            hh[i] = ((f[i]+!f[j])*(!g[j]-g[i]) + (!f[j]-f[i])*(g[i]+!g[j])) * cp(0, 0.25);
            h[i] = (!f[j]-f[i])*(!g[j]-g[i])*cp(-0.25, 0) + (f[i]+!f[j])*(g[i]+!g[j])*cp(0, 0.25);
        }
        dft(h, n, 1);
        dft(hh, n, 1);
        for (int i = 0; i < n; i ++) 
            c[i] = (ll(h[i].x + 0.5) + (ll(hh[i].x + 0.5) % mod << 15) + (ll(h[i].y + 0.5) % mod<<30)) % mod;
    }
    void mul(int *a, int *b,int *c,int n) {
        for (int i = 0; i < n; i ++) 
            f[i] = cp(a[i]), g[i] = cp(b[i]);
        dft(f, n, 0);
        dft(g, n, 0);
        for (int i = 0; i < n; i ++) f[i] = f[i] * g[i];
        dft(f, n, 1);
        for (int i = 0; i < n; i ++) c[i] = int(f[i].x + 0.5);
    }
    //[0, n) * [0, m) = [0, n + m - 2]
    int getlen(int n, int m){
        int len = 1;
        while(len < n + m - 1) len <<= 1;
        return len;
    }
}

const int N=400005;
int arr1[N],arr2[N],arr3[N];
int main(){
    fft::init();
    int n,m; scanf("%d%d",&n,&m);
    n++; m++;
    for (int i=0;i<n;i++) scanf("%d",&arr1[i]);
    for (int i=0;i<m;i++) scanf("%d",&arr2[i]);
    fft::multiply(arr1,arr2,arr3,fft::getlen(n,m));
    for (int i=0;i<=n+m-2;i++) printf("%d ",arr3[i]);
}