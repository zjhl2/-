bool find(int u)
{
    for (int v:link[u])
        if (!vis[v])
        {
            vis[v]=1;
            if (!g[v]||find(g[v]))
            {
                g[v]=u;
                b[u]=v;
                return 1;
            }
        }
    return 0;
}
int HA()
{
    int all=0;
    memset(g,-1,sizeof(g));
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if (find(i)) all++;
    }
    return all;
}


/*
5
3 3
1 1
1 2
2 2
2 3
3 3
最大匹配数：最大匹配的匹配边的数目

最小点覆盖数：选取最少的点，使任意一条边至少有一个端点被选择

最大独立数：选取最多的点，使任意所选两点均不相连

最小路径覆盖数：对于一个 DAG（有向无环图），选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。

定理1：最大匹配数 = 最小点覆盖数（这是 Konig 定理）

定理2：最大匹配数 = 最大独立数

定理3：最小路径覆盖数 = 顶点数 - 最大匹配数
*/
