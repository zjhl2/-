#include<cstdio>
#include<map>
#include<algorithm>
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef map<ll,ll>::iterator itr;
struct P
{
    ll x,y;
    P operator-(const P &t)const
    {
        return {x-t.x,y-t.y};
    }
    ll operator^(P t)
    {
        return x*t.y-y*t.x;
    }
};
ll dot(itr it,ll x,ll y)
{
    return it->X*x+it->Y*y;
}
ll cross(itr l,P p2,itr r)
{
    P p1={l->X,l->Y},p3={r->X,r->Y};
    return (p2-p1)^(p3-p2);
}
struct hull
{
    map<ll,ll>s;
    itr mid,l,r,p1,p2;
    void init() { s.clear(); }
    itr pre(itr it)
    {
        if (it==s.end()) return it;
        if (it==s.begin()) return s.end();
        return --it;
    }
    itr suc(itr it)
    {
        if (it==s.end()) return it;
        return ++it;
    }
    bool inside(P p)
    {
        if (s.empty()) return 0;
        r=s.lower_bound(p.x);
        if (r==s.end()) return 0;
        if (r->X==p.x) return p.y<=r->Y;
        if (r==s.begin()) return 0;
        l=r; l--;
        return cross(l,p,r)>=0;  //下凸壳修改不等号
    }
    void add(P p)
    {
        if (inside(p)) return;
        s[p.x]=p.y;
        mid=s.find(p.x);
        p1=suc(mid); p2=suc(p1);
        while(p1!=s.end()&&p2!=s.end()&&cross(mid,{p1->X,p1->Y},p2)>=0)  //下凸壳修改不等号
            s.erase(p1),p1=p2,p2=suc(p2);
        p1=pre(mid); p2=pre(p1);
        while(p1!=s.end()&&p2!=s.end()&&cross(mid,{p1->X,p1->Y},p2)<=0)  //下凸壳修改不等号
            s.erase(p1),p1=p2,p2=pre(p2);
    }
    ll get(ll x,ll y)
    {
        l=s.begin();
        r=suc(l);
        while(r!=s.end()&&dot(l,x,y)<=dot(r,x,y))
            s.erase(l),l=r,r=suc(r);
        return dot(l,x,y);
    }
}G;
//上凸壳
 
const int N=100005;
int n,C,D;
struct mac
{
    int d,P,R,G;
}a[N];
bool cmp(mac a,mac b){ return a.d<b.d;}
ll f[N];
 
int main()
{
    int cas=0;
    while(scanf("%d%d%d",&n,&C,&D),n+C+D)
    {
        for (int i=1;i<=n;i++)
            scanf("%d%d%d%d",&a[i].d,&a[i].P,&a[i].R,&a[i].G);
        sort(a+1,a+n+1,cmp);
        a[0]={0,0,0,0};
        f[0]=C;
        n++;
        a[n]={D+1,0,0,0};
        G.init();
        G.add({a[0].G,f[0]});
        for (int i=1;i<=n;i++)
        {
            f[i]=G.get(a[i].d,1)-a[i].P;
            if (f[i]>=0) G.add({a[i].G,f[i]+a[i].R-1ll*(a[i].d+1)*a[i].G});
        }
        printf("Case %d: %lld\n",++cas,f[n]);
    }
}