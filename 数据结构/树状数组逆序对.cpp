#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005;
int t,n,i,k;
int a[N],nd[N],rk[N],c[N];
void add(int x)
{
	for (int i=x;i<N;i+=i&-i) c[i]++;
}
int get(int x)
{
	int tmp=0;
	for (int i=x;i>0;i-=i&-i) tmp+=c[i];
	return tmp;
}
bool cmp(int i,int j){return a[i]<a[j];}
int main()
{
	while(~scanf("%d%d",&n,&k))
	{
		for (i=0;i<N;i++) c[i]=0;
		long long ans=0;
		for (i=1;i<=n;i++) scanf("%d",&a[i]),nd[i]=i;
		sort(nd+1,nd+n+1,cmp);
		rk[nd[1]]=1;
		for (i=2;i<=n;i++)
			if (a[nd[i]]==a[nd[i-1]]) rk[nd[i]]=rk[nd[i-1]];
			else rk[nd[i]]=rk[nd[i-1]]+1;
		for (i=1;i<=n;i++) a[i]=rk[i];
		for (i=n;i>=1;i--)
		{
			ans+=get(a[i]-1);
			add(a[i]);
		}
		printf("%lld\n",ans);
	}
}

