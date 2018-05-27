#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;
const int N=40005,M=205;
int base[N],vec[2*N],pre[2*N],cost[2*N],base2[N],vec2[2*M],pre2[2*M],nb[2*M],
    dis[N],ans[M],fa[N],lca[2*M];
bool vis[N];
int t,n,m,i,x,y,z,tot1,tot2;
void add(int x,int y,int z)
{
    tot1++;
    pre[tot1]=base[x]; vec[tot1]=y; cost[tot1]=z; base[x]=tot1;
}
void adq(int x,int y,int i)
{
    tot2++;
    pre2[tot2]=base2[x]; vec2[tot2]=y; nb[tot2]=i; base2[x]=tot2;
}
int find(int x)
{
    if (x==fa[x]) return x;
    else {int tmp=find(fa[x]);fa[x]=tmp;return tmp;}
}
void tarjan(int u)
{
    vis[u]=1;
    fa[u]=u;
    int now=base2[u];
    while(now)
    {
        int v=vec2[now];
        if (vis[v])
        {
            lca[nb[now]]=find(v);
            ans[nb[now]]=dis[u]+dis[v]-2*dis[find(v)];
        }
        now=pre2[now];
    }
    now=base[u];
    while(now)
    {
        int v=vec[now];
        if (!vis[v])
        {
            dis[v]=dis[u]+cost[now],tarjan(v);
            fa[v]=u;
        }
        now=pre[now];
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(base,0,sizeof(base));
        memset(base2,0,sizeof(base2));
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        tot1=tot2=0;
        scanf("%d%d",&n,&m);
        for (i=1;i<n;i++) scanf("%d%d%d",&x,&y,&z),add(x,y,z),add(y,x,z);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            adq(x,y,i); adq(y,x,i);
        }
        tarjan(1);
        for (i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}
