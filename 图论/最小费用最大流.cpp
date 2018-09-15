struct graph{
    const static int INF=0x3f3f3f3f,mxN=4005,mxM=6005;
	int base[mxN],vec[2*mxM],pre[2*mxM],cost[2*mxM],flow[2*mxM],tot;
	int S,T;
	int mincost,maxflow;
	int que[mxN];
	int dis[mxN];
	int pv[mxN],pe[mxN];
	bool vis[mxN];
	void init(){
		tot=1;
		memset(base,0,sizeof(base));
	}
	void link(int x,int y,int f,int z){
        // printf("link: %d %d %d %d\n",x,y,f,z);
		vec[++tot]=y;  pre[tot]=base[x];  base[x]=tot;  cost[tot]=z; flow[tot]=f;
		vec[++tot]=x;  pre[tot]=base[y];  base[y]=tot;  cost[tot]=-z; flow[tot]=0;
	}
	bool spfa(){
		memset(vis,0,sizeof(vis));
		memset(pv,-1,sizeof(pv));
		for (int i=0;i<mxN;i++) dis[i]=INF;
		int head=0,tail=1;
		que[tail]=S;  vis[S]=1;  dis[S]=0;
		while(head!=tail){
			head++;
			head%=mxN;
			int u=que[head];
			vis[u]=0;
			for (int now=base[u];now;now=pre[now])
			if (flow[now]>0){
				int v=vec[now];
				if (dis[u]+cost[now]<dis[v]){
					dis[v]=dis[u]+cost[now];
					pv[v]=u;
					pe[v]=now;
					if (!vis[v]){
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
	void work(){
		mincost=0;
		maxflow=0;
		while(spfa()){
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