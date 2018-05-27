#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50005;
int a[N];
int base[N],vec[2*N],pre[2*N],tot;
int id[N],rd[N],son[N],deep[N],size[N],fa[N],top[N];
int T;
int n;
void link(int x,int y)
{
    vec[++tot]=y; pre[tot]=base[x]; base[x]=tot;
}

struct seg
{
    int ma,mi,fl,fr;
    seg operator+(const seg &t)const
    {
        if (ma==-1) return t;
        if (t.ma==-1) return *this;
        int maa=max(ma,t.ma);
        int mii=min(mi,t.mi);
        int ffl=max(fl,t.fl);
        ffl=max(ffl,ma-t.mi);
        int ffr=max(fr,t.fr);
        ffr=max(ffr,t.ma-mi);
        return {maa,mii,ffl,ffr};
    }
    void operator+=(const int t)
    {
        ma+=t; mi+=t;
    }
}s[4*N];
int lazy[4*N];
void build(int i,int l,int r)
{
    lazy[i]=0;
    if (l==r)
    {
        s[i]={a[rd[l]],a[rd[l]],0};
        return;
    }
    int mid=(l+r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    s[i]=s[i*2]+s[i*2+1];
}
void pd(int i)
{
    if (lazy[i])
    {
        lazy[i*2]+=lazy[i];
        lazy[i*2+1]+=lazy[i];
        s[i*2]+=lazy[i];
        s[i*2+1]+=lazy[i];
        lazy[i]=0;
    }
}
void add(int i,int l,int r,int x,int y,int z)
{
    if (x<=l&&r<=y)
    {
        s[i]+=z;
        lazy[i]+=z;
        return;
    }
    pd(i);
    int mid=(l+r)/2;
    if (x<=mid) add(i*2,l,mid,x,y,z);
    if (y>mid) add(i*2+1,mid+1,r,x,y,z);
    s[i]=s[i*2]+s[i*2+1];
}
seg get(int i,int l,int r,int x,int y)
{
    if (x<=l&&r<=y) return s[i];
    pd(i);
    int mid=(l+r)/2;
    seg tmp={-1,-1,-1,-1};
    if (x<=mid) tmp=tmp+get(i*2,l,mid,x,y);
    if (y>mid) tmp=tmp+get(i*2+1,mid+1,r,x,y);
    return tmp;
}


void dfs1(int u,int d,int p)
{
    fa[u]=p;
    deep[u]=d;
    son[u]=-1;
    size[u]=1;
    for (int now=base[u];now;now=pre[now])
    {
        int v=vec[now];
        if (v==p) continue;
        dfs1(v,d+1,u);
        size[u]+=size[v];
        if (son[u]==-1||size[v]>size[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int p)
{
    top[u]=p;
    id[u]=++T;
    rd[T]=u;
    if (son[u]!=-1) dfs2(son[u],p);
    for (int now=base[u];now;now=pre[now])
    {
        int v=vec[now];
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}

int lca(int x,int y)
{
    int f1=top[x],f2=top[y];
    while(f1!=f2)
    {
        if (deep[f1]<deep[f2]) swap(f1,f2),swap(x,y);
        x=fa[f1],f1=top[x];
    }
    if (deep[x]<deep[y]) swap(x,y);
    return y;
}

seg getseg(int x,int LCA,int v)
{
    seg tmp={-1,-1,-1,-1};
    while(x!=LCA&&deep[top[x]]>deep[LCA])
    {
        tmp=get(1,1,n,id[top[x]],id[x])+tmp;
        add(1,1,n,id[top[x]],id[x],v);
        x=fa[top[x]];
    }
    tmp=get(1,1,n,id[LCA],id[x])+tmp;
    add(1,1,n,id[LCA],id[x],v);
    return tmp;
}
int solve(int x,int y,int v)
{
    int LCA=lca(x,y);

    seg tmp1=getseg(x,LCA,v);
    add(1,1,n,id[LCA],id[LCA],-v);
    seg tmp2=getseg(y,LCA,v);

    int ans=max(tmp1.fl,tmp2.fr);
    ans=max(ans,tmp2.ma-tmp1.mi);
    return ans;
}

int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for (int i=1;i<=n;i++) scanf("%d",&a[i]);
        for (int i=1;i<n;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            link(x,y);
            link(y,x);
        }

        dfs1(1,1,-1);
        dfs2(1,-1);
        build(1,1,n);

        int q;
        scanf("%d",&q);
        while(q--)
        {
            int x,y,v;
            scanf("%d%d%d",&x,&y,&v);
            printf("%d\n",solve(x,y,v));
        }
        tot=T=0;
        for (int i=1;i<=n;i++) base[i]=0;
    }
}