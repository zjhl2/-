#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=100005;
int a[N];

struct NODE
{
	int ls,rs,mx;
	ll cnt;
}tree[N*18];
int tot;
int root[N];
void init()
{
	tot=0;
}
int newnode(int l,int r)
{
	tot++;
	tree[tot]={0,0,0,0};
	return tot;
}
void up(int i)
{
	int ls=tree[i].ls,rs=tree[i].rs;
	tree[i].mx=max(tree[ls].mx,tree[rs].mx);
	tree[i].cnt=0;
	if (tree[ls].mx==tree[i].mx) tree[i].cnt+=tree[ls].cnt;
	if (tree[rs].mx==tree[i].mx) tree[i].cnt+=tree[rs].cnt;
}
int build(int l,int r,int x)
{
	int np=newnode(l,r);
	if (l==r)
	{
		tree[np].mx=1;
		tree[np].cnt=x;
		return np;
	}
	int mid=(l+r)/2;
	if (x<=mid) tree[np].ls=build(l,mid,x);
	else tree[np].rs=build(mid+1,r,x);
	up(np);
	return np;
}
int merge(int x,int y,int l,int r)
{
	if (x==0) return y;
	if (y==0) return x;
	if (l==r)
	{
		tree[x].mx+=tree[y].mx;
		return x;
	}
	int mid=(l+r)/2;
	tree[x].ls=merge(tree[x].ls,tree[y].ls,l,mid);
	tree[x].rs=merge(tree[x].rs,tree[y].rs,mid+1,r);
	up(x);
	return x;
}

vector<int>link[N];
ll f[N];
int n;
void dfs(int u,int fa)
{
	root[u]=build(1,n,a[u]);
	for (int i=0;i<link[u].size();i++)
	{
		int v=link[u][i];
		if (v==fa) continue;
		dfs(v,u);
		merge(root[u],root[v],1,n);
	}
	f[u]=tree[root[u]].cnt;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		link[x].push_back(y);
		link[y].push_back(x);
	}
	init();
	dfs(1,1);
	for (int i=1;i<=n;i++) printf("%lld ",f[i]);
	for (int i=1;i<=n;i++) link[i].clear();

}
/*

http://codeforces.com/contest/600/problem/E

*/


树上所有简单路径的lis

#include<bits/stdc++.h>
using namespace std;

const int N=100005;

int n;
int ans;
int val[N];

struct NODE
{
	int ls,rs,lis,lds;
}tree[N*18];
int tot;
int root[N];
void init()
{
	tot=0;
}
int newnode()
{
	tot++;
	tree[tot]={0,0,0,0};
	return tot;
}
void up(int i)
{
	int ls=tree[i].ls,rs=tree[i].rs;
	tree[i].lis=max(tree[ls].lis,tree[rs].lis);
	tree[i].lds=max(tree[ls].lds,tree[rs].lds);
}
int build(int l,int r,int x,int lis,int lds)
{
	int np=newnode();
	if (l==r)
	{
		tree[np].lis=lis;
		tree[np].lds=lds;
		return np;
	}
	int mid=(l+r)/2;
	if (x<=mid) tree[np].ls=build(l,mid,x,lis,lds);
	else tree[np].rs=build(mid+1,r,x,lis,lds);
	up(np);
	return np;
}
int merge(int x,int y,int l,int r,int tp=0)
{
	if (x==0) return y;
	if (y==0) return x;
	if (l==r)
	{
		tree[x].lis=max(tree[x].lis,tree[y].lis);
		tree[x].lds=max(tree[x].lds,tree[y].lds);
		return x;
	}
	if (tp==0)
	{
		ans=max(ans,tree[tree[x].ls].lis+tree[tree[y].rs].lds);
		ans=max(ans,tree[tree[x].rs].lds+tree[tree[y].ls].lis);
	}
	int mid=(l+r)/2;
	tree[x].ls=merge(tree[x].ls,tree[y].ls,l,mid,tp);
	tree[x].rs=merge(tree[x].rs,tree[y].rs,mid+1,r,tp);
	up(x);
	return x;
}

int getlis(int i,int l,int r,int x,int y)
{
	if (x>y) return 0;
	if (x<=l&&r<=y) return tree[i].lis;
	int mid=(l+r)/2;
	int ret=0;
	if (x<=mid) ret=max(ret,getlis(tree[i].ls,l,mid,x,y));
	if (y>mid) ret=max(ret,getlis(tree[i].rs,mid+1,r,x,y));
	return ret;
}
int getlds(int i,int l,int r,int x,int y)
{
	if (x>y) return 0;
	if (x<=l&&r<=y) return tree[i].lds;
	int mid=(l+r)/2;
	int ret=0;
	if (x<=mid) ret=max(ret,getlds(tree[i].ls,l,mid,x,y));
	if (y>mid) ret=max(ret,getlds(tree[i].rs,mid+1,r,x,y));
	return ret;
}
int f[N],g[N];
vector<int>link[N];
int dfs(int u,int fa)
{
	if (u==2)
		u=2;
	int np=0;
	for (auto v:link[u])
	{
		if (v==fa) continue;
		dfs(v,u);
		ans=max(ans,getlis(np,1,n,1,val[u]-1)+getlds(root[v],1,n,val[u]+1,n)+1);
		ans=max(ans,getlds(np,1,n,val[u]+1,n)+getlis(root[v],1,n,1,val[u]-1)+1);

		np=merge(np,root[v],1,n);
	}
	if (u==2)
		u=2;
	int lis=getlis(np,1,n,1,val[u]-1);
	int lds=getlds(np,1,n,val[u]+1,n);
	f[u]=lis+1; g[u]=lds+1;
	root[u]=build(1,n,val[u],lis+1,lds+1);
	root[u]=merge(np,root[u],1,n,1);
}

int mx[N];
int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		init();
		scanf("%d",&n);
		for (int i=1;i<=n;i++) val[i]=i;//scanf("%d",&val[i]),mx[i]=val[i];
//		sort(mx+1,mx+n+1);
//		for (int i=1;i<=n;i++) val[i]=lower_bound(mx+1,mx+n+1,val[i])-mx;
		for (int i=1;i<n;i++)
		{
			int x,y; scanf("%d%d",&x,&y);
			link[x].push_back(y);
			link[y].push_back(x);
		}
		ans=1;
        dfs(1,1);
        ans=max(ans,getlis(root[1],1,n,1,n));
        ans=max(ans,getlds(root[1],1,n,1,n));
        printf("%d\n",ans);

        for (int i=1;i<=n;i++) link[i].clear();
	}
}

http://www.spoj.com/problems/LISTREE/