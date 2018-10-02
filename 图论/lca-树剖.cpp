#include<bits/stdc++.h>
using namespace std;

const int N=100005;
vector<int> link[N];
int fa[N];
int deep[N];
int sz[N],son[N];
void dfs(int u,int _fa,int _deep){
	deep[u]=_deep;
	fa[u]=_fa;
	sz[u]=1;
	son[u]=-1;
	for (int v:link[u]){
		if (v==_fa) continue;
		dfs(v,u,_deep+1);
		sz[u]+=sz[v];
		if (son[u]==-1||sz[v]>sz[son[u]]) son[u]=v;
	}
}
int top[N],id[N],T;
void dfs2(int u,int _fa,int p){
    top[u]=p;
    id[u]=++T;
    if (son[u]!=-1) dfs2(son[u],u,p);
	for (int v:link[u]){
        if (v==_fa||v==son[u]) continue;
        dfs2(v,u,v);
    }
}
int getlca(int x,int y){
    int f1=top[x],f2=top[y];
    while(f1!=f2){
        if (deep[f1]<deep[f2]) swap(f1,f2),swap(x,y);
        x=fa[f1],f1=top[x];
    }
    if (deep[x]<deep[y]) swap(x,y);
    return y;
}
int get(int l,int r,int tp=3){
    //线段树根据tp区间操作
}
int line(int x,int lca){
    int ret=0;
    while(x!=lca&&deep[top[x]]>deep[lca]){
        ret+=get(id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if (x!=lca) ret+=get(id[lca]+1,id[x]);
    return ret;
}
int route(int x,int y){
    int lca=getlca(x,y);
    int ret1=line(x,lca);
    int ret2=line(y,lca);
    int ret3=get(id[lca],id[lca]);
    return ret1+ret2+ret3;
}