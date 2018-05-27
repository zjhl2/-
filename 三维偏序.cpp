#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;

struct P
{
	int x,y,z;
}a[N];
bool cmpx(P a,P b)
{
	return a.x<b.x;
}
bool cmpy(int i,int j)
{
	return a[i].y<a[j].y;
}

int c[N];
void add(int x,int y)
{
	for (int i=x;i<N;i+=i&-i) c[i]+=y;
}
int get(int x)
{
	int ret=0;
	for (int i=x;i;i-=i&-i) ret+=c[i];
	return ret;
}
int f[N];
int nd1[N],nd2[N];
void solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)/2;
	for (int i=l;i<=mid;i++) nd1[i]=i;
	for (int j=mid+1;j<=r;j++) nd2[j]=j;
	sort(nd1+l,nd1+mid+1,cmpy);
	sort(nd2+mid+1,nd2+r+1,cmpy);

	int i=l;
	for (int j=mid+1;j<=r;j++)
	{
		while(i<=mid&&a[nd1[i]].y<a[nd2[j]].y) add(a[nd1[i]].z,1),i++;
		f[nd2[j]]+=get(a[nd2[j]].z);
	}

	i=l;
	for (int j=mid+1;j<=r;j++)
	{
		while(i<=mid&&a[nd1[i]].y<a[nd2[j]].y) add(a[nd1[i]].z,-1),i++;
	}
	solve(l,mid);
	solve(mid+1,r);
}
int main()
{
	int n; scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+n+1,cmpx);
	solve(1,n);
	ll ans=1ll*n*(n-1)/2;
	for (int i=1;i<=n;i++) ans-=f[i];
	printf("%lld\n",ans);
}
