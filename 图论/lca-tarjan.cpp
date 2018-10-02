#include<bits/stdc++.h>
using namespace std;

const int N=100005;
struct P{
    int x,y;
}a[N],Q[N];
vector<P> link[N];
vector<P> VQ[N];

int dis[N],deep[N];
void dfs(int u,int _fa,int _dis,int _deep){
    dis[u]=_dis;
    deep[u]=_deep;
    for (P p:link[u]){
        int v=p.x,w=p.y;
        if (v==_fa) continue;
        dfs(v,u,_dis+w,_deep+1);
    }
}

int fa[N];
int find(int x){
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

bool vis[N];
int lca[N];
void tarjan(int u,int _fa){
	vis[u]=1;
	for (P p:VQ[u]){
		int v=p.x,id=p.y;
		if (vis[v]) 
			lca[id]=find(v);
	}
	for (P p:link[u]){
		int v=p.x;
		if (v==_fa) continue;
		tarjan(v,u);
		fa[v]=u;
	}
}
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n,m; scanf("%d%d",&n,&m);
        for (int i=1;i<n;i++){
            int x,y,w; scanf("%d%d%d",&x,&y,&w);
            link[x].push_back({y,w});
            link[y].push_back({x,w});
        }
		dfs(1,0,0,0);
        for (int i=1;i<=m;i++){
			scanf("%d%d",&Q[i].x,&Q[i].y);
			VQ[Q[i].x].push_back({Q[i].y,i});
			VQ[Q[i].y].push_back({Q[i].x,i});
		}
		for (int i=1;i<=n;i++) fa[i]=i;
		tarjan(1,0);
		for (int i=1;i<=m;i++)
			printf("%d\n",dis[Q[i].x]+dis[Q[i].y]-2*dis[lca[i]]);
    }
}
// hdu2586