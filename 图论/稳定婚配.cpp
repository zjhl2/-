bool better(int w,int m1,int m2)
{
    return rk[w][m1]<rk[w][m2];
}
void GS()
{
    queue<int>Q;
    for (int i=1;i<=n;i++) mp[i]=wp[i]=0,Q.push(i),now[i]=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        int v=sa[u][now[u]];
        if (wp[v]==0||better(v,u,wp[v]))
        {
            if (wp[v]) mp[wp[v]]=0,Q.push(wp[v]);
            wp[v]=u;
            mp[u]=v;
            now[u]++;
        }
        else Q.push(u),now[u]++;
    }
}