int cent,mxsz;
int size[N];
int vis[N];
void findcent(int u,int fa,int n)
{
	size[u]=1;
	int mx=0;
	for (int v:link[u])
	{
		if (vis[v]||v==fa) continue;
		findcent(v,u,n);
		size[u]+=size[v];
		mx=max(mx,size[v]);
	}
	mx=max(mx,n-size[u]);
	if (mx<=mxsz) cent=u,mxsz=mx;
}

void solve(int u,int n)
{
	cent=u;  mxsz=n;
	findcent(u,-1,n);
	u=cent;
	f[u].reset();
	f[u].set(w[u]);
    dfs(u,-1);
    ans|=f[u];
    vis[u]=1;
    for (int v:link[u])
    {
        if (vis[v]) continue;
        if (size[v]<size[u]) solve(v,size[v]);
        else solve(v,n-size[u]);
    }
}





#include<bits/stdc++.h>
using namespace std;

const int N=100005,INF=0x3f3f3f3f;

struct P
{
	int v,z;
};
vector<P>link[N];
int ans;
int g[N];

int vis[N];
int cent,mxsz;
int size[N];
void findcent(int u,int fa,int n)
{
	size[u]=1;
	int mx=0;
	for (P tmp:link[u])
	{
		int v=tmp.v;
		if (vis[v]||v==fa) continue;
		findcent(v,u,n);
		size[u]+=size[v];
		mx=max(mx,size[v]);
	}
	mx=max(mx,n-size[u]);
	if (mx<mxsz) cent=u,mxsz=mx;
}

map<int,int>S;
void dfs(int u,int fa,int now,int minnow,int deep)
{
	auto it=S.lower_bound(-minnow);
	if (it!=S.end()) ans=max(ans,it->second+deep+1);
	for (P tmp:link[u])
	{
		int v=tmp.v,z=tmp.z;
		if (vis[v]||v==fa) continue;
		dfs(v,u,now+g[u]-z,min(now+g[u]-z,minnow),deep+1);
	}
}
void adjust(auto it)
{
	auto nxt=it; nxt++;
	if (nxt!=S.end()&&nxt->second>=it->second)
	{
		S.erase(it);
		return;
	}
	while(it!=S.begin())
	{
		auto pre=it; pre--;
		if (pre->second<=it->second) S.erase(pre);
		else break;
	}
}
void add(int u,int fa,int now,int minnow,int deep)
{
	if (minnow>=0)
	{
		auto it=S.find(now);
		if (it==S.end()||it->second<deep)
		{
			S[now]=deep;
			adjust(S.find(now));
		}
	}
	for (P tmp:link[u])
	{
		int v=tmp.v,z=tmp.z;
		if (vis[v]||v==fa) continue;
		add(v,u,now+g[v]-z,min(0,minnow+g[v]-z),deep+1);
	}
}
void solve(int u,int n)
{
	cent=u;  mxsz=n;
	findcent(u,-1,n);
	u=cent;
	vis[u]=1;

	S.clear();	S[0]=0;
	for (int i=0;i<link[u].size();i++)
	{
		int v=link[u][i].v,z=link[u][i].z;
		if (vis[v]) continue;
		dfs(v,u,g[u]-z,g[u]-z,1);
		add(v,u,g[v]-z,min(0,g[v]-z),1);
	}
	for (auto it:S) ans=max(ans,it.second+1);

	S.clear();	S[0]=0;
	for (int i=link[u].size()-1;i>=0;i--)
	{
		int v=link[u][i].v,z=link[u][i].z;
		if (vis[v]) continue;
		dfs(v,u,g[u]-z,g[u]-z,1);
		add(v,u,g[v]-z,min(0,g[v]-z),1);
	}
	for (auto it:S) ans=max(ans,it.second+1);

    for (P tmp:link[u])
	{
		int v=tmp.v;
		if (vis[v]) continue;
		solve(v,size[v]);
	}
}
int main()
{
	int n; scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&g[i]);
	for (int i=1;i<n;i++)
	{
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		link[x].push_back({y,z});
		link[y].push_back({x,z});
	}
	ans=1;
	solve(1,n);
	printf("%d\n",ans);
}
https://cn.vjudge.net/contest/191234#problem/K
树分治+平衡树维护单调队列

http://uoj.ac/submission/230324
购票
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200005;
struct E
{
	int v; ll z;
};
vector<E>link[N];
ll d[N],p[N],q[N],l[N],f[N];
int fa[N];

struct P
{
	ll d,f;
	ll operator*(const P &b)const
	{
		return d*b.d+f*b.f;
	}
}stk[N];
int top;
long double slope(P a,P b)
{
    long double tmp=1.0;
    return tmp*(b.f-a.f)/(b.d-a.d);
}
void add(P p)
{
	if (top<=1)
	{
		stk[top++]=p;
		return;
	}
	while(top>=2&&slope(p,stk[top-1])>slope(stk[top-1],stk[top-2])) top--;
	stk[top++]=p;
}
void upd(int id)
{
	P vec={-p[id],1};
	int l=0,r=top-1;
	while(l<r)
	{
		int mid=(l+r)/2;
		if (vec*stk[mid]>vec*stk[mid+1]) l=mid+1;
		else r=mid;
	}
	f[id]=min(f[id],p[id]*d[id]+q[id]+vec*stk[l]);
}

int cent,mxsz;
int size[N];
int vis[N];
void findcent(int u,int n)
{
	size[u]=1;
	int mx=0;
	for (E e:link[u])
	{
		int v=e.v;
		if (vis[v]) continue;
		d[v]=d[u]+e.z;
		findcent(v,n);
		size[u]+=size[v];
		mx=max(mx,size[v]);
	}
	mx=max(mx,n-size[u]);
	if (mx<=mxsz) cent=u,mxsz=mx;
}

int nd[N],tot;
void add(int u)
{
	nd[tot++]=u;
	for (E e:link[u])
		if (!vis[e.v]) add(e.v);
}
bool cmp(int i,int j)
{
	return d[i]-l[i]>d[j]-l[j];
}
void solve(int u,int n)
{
	if (n==1) return;
	cent=u;  mxsz=n;
	findcent(u,n);
	int rt=cent;
	for (E e:link[rt]) vis[e.v]++;
	if (u==4&&n==2)
		u=4;
	solve(u,n-size[rt]+1);

	for (E e:link[rt]) vis[e.v]--;
	for (E e:link[rt]) add(e.v);
	sort(nd,nd+tot,cmp);
	int now=rt;
	for (int i=0;i<tot;i++)
	{
		int id=nd[i];
		while(now!=fa[u]&&d[now]>=d[id]-l[id]) add({d[now],f[now]}),now=fa[now];
		if (top) upd(id);
	}
	tot=0; top=0;
	for (E e:link[rt]) solve(e.v,size[e.v]);
}
int main()
{
	int n,t; scanf("%d%d",&n,&t);
	for (int i=2;i<=n;i++)
	{
		f[i]=1ll<<62;
		ll s; scanf("%d%lld",&fa[i],&s);
		link[fa[i]].push_back({i,s});
		scanf("%lld%lld%lld",&p[i],&q[i],&l[i]);
	}
	solve(1,n);
	for (int i=2;i<=n;i++) printf("%lld\n",f[i]);
}
