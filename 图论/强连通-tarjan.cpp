bool vis[N],is[N];
void tarjan(int u)
{
    T++;
    dfn[u]=T; low[u]=T; stk[++top]=u; is[u]=true; vis[u]=true;
    for (int v:vec[u])
    {
        if (!vis[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
        if (is[v]) low[u]=min(low[u],dfn[v]);
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
        belong[u]=u; is[u]=0; top--;
    }
}
/*
我们可以发现有两类节点可以成为割点：

1.对根节点u，若其有两棵或两棵以上的子树，则该根结点u为割点；
2.对非叶子节点u（非根节点），若其子树的节点均没有指向u的祖先节点的回边，说明删除u之后，根结点与u的子树的节点不再连通；则节点u为割点。
*/