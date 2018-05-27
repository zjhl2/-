#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;

struct line
{
	int l,r,y,tp;
	bool operator<(const line &b)const
	{
		return y<b.y;
	}
}a[2*N];
int sum[2*N*4],cnt[2*N*4];
int mem[2*N];
void up(int i,int l,int r)
{
	if (cnt[i]) sum[i]=mem[r]-mem[l];
	else
	{
		if (l+1<r) sum[i]=sum[i*2]+sum[i*2+1];
		else sum[i]=0;
	}
}
void add(int i,int l,int r,int x,int y,int z)
{
	if (x<=l&&r<=y)
	{
		cnt[i]+=z;
		up(i,l,r);
		return;
	}
	int mid=(l+r)/2;
	if (x<mid) add(i*2,l,mid,x,y,z);
	if (y>mid) add(i*2+1,mid,r,x,y,z);
	up(i,l,r);
}
int main()
{
	int n; scanf("%d",&n);
	int tot=0;
	for (int i=1;i<=n;i++)
	{
		int x1,y1,x2,y2; scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		a[++tot]={min(x1,x2),max(x1,x2)+1,min(y1,y2),1};
		mem[tot]=min(x1,x2);
		a[++tot]={min(x1,x2),max(x1,x2)+1,max(y1,y2)+1,-1};
		mem[tot]=max(x1,x2)+1;
	}
	sort(mem+1,mem+tot+1);
	sort(a+1,a+tot+1);
	ll ans=0;
	for (int i=1;i<=tot;i++)
	{
		int l=lower_bound(mem+1,mem+tot+1,a[i].l)-mem;
		int r=lower_bound(mem+1,mem+tot+1,a[i].r)-mem;
		ans+=1ll*sum[1]*(a[i].y-a[i-1].y);
		add(1,1,tot,l,r,a[i].tp);
	}
	printf("%lld\n",ans);
}
//坐标线相交处为点坐标
