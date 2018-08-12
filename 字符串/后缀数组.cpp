#include<bits/stdc++.h>
using namespace std;

const int maxn=100005;
int wa[maxn], wb[maxn], wv[maxn], Ws[maxn];
int sa[maxn], rk[maxn], ht[maxn];
int cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}
void da(char *r, int n, int m = 128) {
    int *x = wa, *y = wb, *t, i, j, k, p;
    for(i = 0; i < m; i++) Ws[i] = 0;
    for(i = 0; i < n; i++) Ws[x[i] = r[i]]++;
    for(i = 1; i < m; i++) Ws[i] += Ws[i - 1];
    for(i = n - 1; i >= 0; i--) sa[--Ws[x[i]]] = i;
    for(j = 1, p = 1; p < n; j <<= 1, m = p) {
        for(p = 0, i = n - j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i = 0; i < n; i++) wv[i] = x[y[i]];
        for(i = 0; i < m; i++) Ws[i] = 0;
        for(i = 0; i < n; i++) Ws[wv[i]]++;
        for(i = 1; i < m; i++) Ws[i] += Ws[i - 1];
        for(i = n - 1; i >= 0; i--) sa[--Ws[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    i = j = k =0; n--;
    for(i = 1; i <= n; i++) rk[sa[i]] = i;
    for(i = 0; i < n; ht[rk[i++]] = k)
        for(k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; k++);
};

const int N=100005;
char s[N];
int main() {
    scanf("%s",s);
    int n=strlen(s);
    da(s,n+1);
    for (int i=1;i<=n;i++) printf("%d ",sa[i]+1); puts("");
    for (int i=2;i<=n;i++) printf("%d ",ht[i]);
}