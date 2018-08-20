#include<bits/stdc++.h>
using namespace std;

const int M=4000005;
const int N=100005,INF=0x3f3f3f3f;

int tot;
int ls[M],rs[M],val[M];

void up(int i){
    val[i]=min(val[ls[i]],val[rs[i]]);
}

int build(int l,int r,int x,int y){
    int np=++tot;
	if (l==r){
        val[np]=y;
		return np;
	}
	int mid=(l+r)/2;
	if (x<=mid) ls[np]=build(l,mid,x,y);
	else rs[np]=build(mid+1,r,x,y);
	up(np);
	return np;
}

int merge(int x,int y,int l,int r){
    if (x==0||y==0) return x+y;
    int np=++tot;
    if (l==r){
        val[np]=min(val[x],val[y]);
        return np;
    }
    int mid=(l+r)/2;
    ls[np]=merge(ls[x],ls[y],l,mid);
    rs[np]=merge(rs[x],rs[y],mid+1,r);
    up(np);
    return np;
}

int query(int i,int l,int r,int x,int y){
    if (x<=l&&r<=y) return val[i];
    int mid=(l+r)/2;
    int ret=INF;
    if (x<=mid) ret=min(ret,query(ls[i],l,mid,x,y));
    if (y>mid) ret=min(ret,query(rs[i],mid+1,r,x,y));
    return ret;
}

int a[N];
vector<int>link[N];
int root[N];
int n,r,m; 
int deep[N];

void dfs(int u,int _fa){
    deep[u]=deep[_fa]+1;
    root[u]=build(1,n,deep[u],a[u]);
    for (int v:link[u]){
        if (v==_fa) continue;
        dfs(v,u);
        root[u]=merge(root[u],root[v],1,n);
    }
}

int main(){
    val[0]=INF;
    scanf("%d%d",&n,&r);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        link[x].emplace_back(y);
        link[y].emplace_back(x);
    }
    dfs(r,0);
    scanf("%d",&m);
    int last=0;
    while(m--){
        int p,q; scanf("%d%d",&p,&q);
        int x=(p+last)%n+1,k=(q+last)%n;
        last=query(root[x],1,n,deep[x],deep[x]+k);
        printf("%d\n",last);
    }
}