#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=50005;
const ll INF=0x3f3f3f3f3f3f3f3fll;
int n;
ll ans[N];
int nxt[N];
struct P
{
    int x,y;
    bool operator<(const P &t)const
    {
        return x<t.x||x==t.x&&y>t.y;
    }
    P operator-(const P &t)
    {
        return {x-t.x,y-t.y};
    }
    ll operator*(const P &t)
    {
        return 1ll*x*t.x+1ll*y*t.y;
    }
    ll operator^(const P &t)
    {
        return 1ll*x*t.y-1ll*y*t.x;
    }
}a[N];
ll cross(P a,P b,P c)
{
    return (b-a)^(c-b);
}
map<P,int>mp;
struct hull
{
    int n,top;
    P a[N],stk[N];
    void init()
    {
        n=0;
    }
    void add(P p)
    {
        a[++n]=p;
    }
    void make()
    {
        sort(a+1,a+n+1);
        top=0;
        for (int i=1;i<=n;i++)
        {
            while(top>1&&cross(stk[top-1],stk[top],a[i])>=0) top--;
            stk[++top]=a[i];
        }
    }
    ll get(P p)
    {
        if (top==0) return -INF;
        int l=1,r=top;
        while(l<r)
        {
            int mid=(l+r)/2;
            if (p*stk[mid]<p*stk[mid+1]) l=mid+1;else r=mid;
        }
        return p*stk[l];
    }
}up,down;