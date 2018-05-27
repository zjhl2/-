bool vis[N],on[N];
int l[N],r[N];
vector<int>link[N];
int dfs1(int u,int fa)
{
    vis[u]=1;
    for (int i=0;i<link[u].size();i++)
    {
        int v=link[u][i];
        if (v==fa) continue;
        l[v]=u;
        if (vis[v]) return v;
        int tmp=dfs1(v,u);
        if (tmp) return tmp;
    }
    return 0;
}

for (int i=1;i<=n;i++) vis[i]=0,on[i]=0;
int root=dfs1(1,1);
r[l[root]]=root; on[root]=1;
for (int i=l[root];i!=root;i=l[i])  r[l[i]]=i,on[i]=1;