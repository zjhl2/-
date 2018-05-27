#include<cstdio>
#include<queue>
using namespace std;
const int N=100005,M=100005;
int vec[2*M],pre[2*M],base[N],c[2*M],tot;
int dis[N];
int n,m,u,v,w,i;
void link(int x,int y,int z)
{
	vec[++tot]=y; pre[tot]=base[x]; base[x]=tot; c[tot]=z;
}
struct dot{
	int id,dis;
	bool operator<(const dot &b) const
	{
		return dis>b.dis;
	}
};
void dij(int S)
{
	for (i=1;i<=n;i++) dis[i]=-1;
	priority_queue<dot>p;
	p.push({S,0});
	while(!p.empty())
	{
		if (dis[p.top().id]!=-1) {p.pop(); continue;}
		int u=p.top().id; dis[u]=p.top().dis; p.pop();
		for (int now=base[u];now;now=pre[now])
		{
			int v=vec[now];
			if (dis[v]==-1) p.push({v,dis[u]+c[now]});
		}
	}
}
int main()
{
	while(~scanf("%d%d",&n,&m)&&n)
	{
		tot=0;
		for (i=1;i<=n;i++) base[i]=0;
		for (i=1;i<=m;i++) scanf("%d%d%d",&u,&v,&w),link(u,v,w),link(v,u,w);
		dij(1);
		printf("%d\n",dis[n]);
	}
}
