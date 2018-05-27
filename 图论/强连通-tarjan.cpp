#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=10005,M=100005;
int dfn[N],low[N],n,m,i,stk[N],belong[N],top,T,tot,cnt,x,y;
int pre[M],base[N],vec[M];
bool vis[N],is[N];
void add(int x,int y)
{
    tot++; pre[tot]=base[x];  base[x]=tot; vec[tot]=y;
}
void tarjan(int u)
{
    T++;
    dfn[u]=T; low[u]=T; stk[++top]=u; is[u]=true; vis[u]=true;
    int now=base[u];
    while(now)
    {
        int v=vec[now];
        if (!vis[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
        if (is[v]) low[u]=min(low[u],dfn[v]);
        now=pre[now];
    }
    if (low[u]==dfn[u])
    {
        cnt++;
        while(stk[top]!=u)
        {
            belong[stk[top]]=u;
            is[stk[top]]=0;
            top--;
        }
    }
}
int main()
{
    while(~scanf("%d%d",&n,&m)&&n)
    {
        cnt=0; T=0; tot=0;
        memset(vis,0,sizeof(vis));
        memset(base,0,sizeof(base));
        for (i=1;i<=m;i++) scanf("%d%d",&x,&y),add(x,y);
        for (i=1;i<=n;i++)
            if (!vis[i]) tarjan(i);
        printf(cnt==1?"Yes\n":"No\n");
    }
}

