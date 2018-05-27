#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=310,INF=0x3f3f3f3f;
const int mxN=310,mxM=6010;
int n;
int in[N];
int S,T;
struct graph{
	int base[mxN],vec[2*mxM],pre[2*mxM],cost[2*mxM],flow[2*mxM],tot;
	int S,T;
	int mincost,maxflow;
	int que[mxN];
	int dis[mxN];
	int pv[mxN],pe[mxN];
	bool vis[N];
	void init()
	{
		tot=1;
		memset(base,0,sizeof(base));
	}
	void link(int x,int y,int f,int z)
	{
		vec[++tot]=y;  pre[tot]=base[x];  base[x]=tot;  cost[tot]=z; flow[tot]=f;
		vec[++tot]=x;  pre[tot]=base[y];  base[y]=tot;  cost[tot]=-z; flow[tot]=0;
	}
	bool spfa()
	{
		memset(vis,0,sizeof(vis));
		memset(pv,-1,sizeof(pv));
		for (int i=0;i<mxN;i++) dis[i]=INF;
		int head=0,tail=1;
		que[tail]=S;  vis[S]=1;  dis[S]=0;
		while(head!=tail)
		{
			head++;
			head%=mxN;
			int u=que[head];
			vis[u]=0;

			for (int now=base[u];now;now=pre[now])
			if (flow[now]>0)
			{
				int v=vec[now];
				if (dis[u]+cost[now]<dis[v])
				{
					dis[v]=dis[u]+cost[now];
					pv[v]=u;
					pe[v]=now;
					if (!vis[v])
					{
						vis[v]=1;
						tail++;
						tail%=mxN;
						que[tail]=v;
					}
				}
			}
		}
		if (dis[T]!=INF) return 1;
		else return 0;
	}
	void work()
	{
		mincost=0;
		maxflow=0;
		while(spfa())
		{
			int mxf=INF;
			for (int v=T;v!=S;v=pv[v])
				mxf=min(mxf,flow[pe[v]]);
			maxflow+=mxf;
			mincost+=mxf*dis[T];
			for (int v=T;v!=S;v=pv[v])
				flow[pe[v]]-=mxf,flow[pe[v]^1]+=mxf;
		}
	}
}G;
int main()
{
	G.init();
	scanf("%d",&n);
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		int k; scanf("%d",&k);
		for (int j=1;j<=k;j++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			G.link(i,x,INF,y);
			ans+=y;
			in[i]-=1;
			in[x]+=1;
		}
	}
	for (int i=2;i<=n;i++) G.link(i,1,INF,0);
	S=0;  T=n+1;
	for (int i=1;i<=n;i++)
	{
		if (in[i]>0) G.link(S,i,in[i],0);
		if (in[i]<0) G.link(i,T,-in[i],0);
	}
	G.S=S;  G.T=T;
	G.work();
	printf("%d\n",ans+G.mincost);
}
