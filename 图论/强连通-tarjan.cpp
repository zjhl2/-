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
