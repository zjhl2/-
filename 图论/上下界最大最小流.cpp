    int S=R+C+1,T=R+C+2;
    int SS=T+1,TT=T+2;
    for (int i=1;i<=R;i++)
    {
        G.link(S,i,up[i]-down[i]);
        in[i]+=down[i];
        out[S]+=down[i];
    }
    for (int i=R+1;i<=R+C;i++)
    {
        G.link(i,T,up[i]-down[i]);
        out[i]+=down[i];
        in[T]+=down[i];
    }
    int maxflow=0;
    for (int i=1;i<=T;i++)
    {
        if (in[i]>out[i]) G.link(SS,i,in[i]-out[i]),maxflow+=in[i]-out[i];
        if (out[i]>in[i]) G.link(i,TT,out[i]-in[i]);
    }
    int ret1=0;
    G.S=SS; G.T=TT;
    ret1=G.dinic();

    G.link(T,S,INF);
    int ret2=G.dinic();
    if (ret1+ret2!=maxflow)
    {
        printf("-1\n");
        return 0;
    }
//ret2为最小流量
//最大流就是再跑一次S到T的最大流