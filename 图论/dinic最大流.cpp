
const int mxN=100005,mxM=100005,INF=0x3f3f3f3f;
struct graph{
    int S,T;
    int base[mxN],vec[mxM],pre[mxM],tot;
    int c[mxM];
    int d[mxN],q[mxN];
    bool vis[mxN];
    void init()
    {
        memset(base,0,sizeof(base));
        tot=1;
    }
    void link(int x,int y,int z)
    {
        vec[++tot]=y; pre[tot]=base[x]; base[x]=tot; c[tot]=z;
        vec[++tot]=x; pre[tot]=base[y]; base[y]=tot; c[tot]=0;
    }
    bool bfs()
    {
        int head=0,tail=0;
        memset(d,-1,sizeof(d));
        d[S]=0;
        q[++tail]=S;
        while(head<tail)
        {
            head++;
            int u=q[head];
            for (int now=base[u];now;now=pre[now])
            {
                int v=vec[now];
                if (d[v]==-1&&c[now]>0)
                {
                    d[v]=d[u]+1;
                    q[++tail]=v;
                    if (v==T) return 1;
                }
            }
        }
        return 0;
    }
    int dfs(int u,int flow)
    {
        int r=0;
        if (u==T) return flow;
        for (int now=base[u];now&&r<flow;now=pre[now])
        {
            int v=vec[now];
            if (c[now]>0&&d[v]==d[u]+1)
            {
                int x=min(c[now],flow-r);
                x=dfs(v,x);
                r+=x;
                c[now]-=x;
                c[now^1]+=x;
            }
        }
        if (!r)d[u]=-2;
        return r;
    }
    int dinic()
    {
        int ans=0;
        while(bfs())
            ans+=dfs(S,INF);
        return ans;
    }
}G;