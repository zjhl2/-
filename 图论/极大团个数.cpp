#include<cstdio>
const int N=150;
int a[N][N];
int num[N],n,m,x,y,ans,sum;
void dfs(int *pw,int ptw,int *pp,int ptp)
{
    if (ptw==0&&ptp==0) sum++;
    if (sum>1000) return;
    int cnt[N]={0};
    int id=1;
    for (int i=1;i<=ptw;i++)
	{
		for (int j=1;j<=ptw;j++)
			if (a[pw[i]][pw[j]]) cnt[i]++;
		if (cnt[i]>cnt[id]) id=i;
	}
    int wait[N],tw;
    int past[N],tp;
    int v=pw[id];
    for (int i=1;i<=ptw;i++)
    {
        int u=pw[i];
        if (a[v][u]) continue;
        tw=0;
        for (int j=1;j<=ptw;j++)
            if (a[u][pw[j]]) wait[++tw]=pw[j];
        tp=0;
        for (int j=1;j<=ptp;j++)
            if (a[u][pp[j]]) past[++tp]=pp[j];
        dfs(wait,tw,past,tp);
        pw[i]=0,pp[++ptp]=u;
    }
}
void solve()
{
    sum=0;
    int wait[N],tw=0;
    for (int j=1;j<=n;j++) wait[++tw]=j;
    int past[N],tp=0;
    dfs(wait,tw,past,tp);
    if (sum>1000) printf("Too many maximal sets of friends.\n");
    else printf("%d\n",sum);
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++) a[i][j]=0;
        while(m--)
        {
            scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=1;
        }
        solve();
    }
}

