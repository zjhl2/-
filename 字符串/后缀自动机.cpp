#include<bits/stdc++.h>
using namespace std;

const int N=600005;

int tot,root,last;
int pa[N],deep[N],ch[N][27],cnt[N]; //两倍
int newnode(int _deep)
{
	tot++;
	memset(ch[tot],0,sizeof(ch[tot]));
	deep[tot]=_deep;
	cnt[tot]=0;
	return tot;
}
void init()
{
	tot=0;
	root=newnode(0);
	last=root;
}
void insert(int w)
{
	int np=newnode(deep[last]+1);
	int u=last;
	while(u&&!ch[u][w]) ch[u][w]=np,u=pa[u];
	if (!u) pa[np]=root;
	else
	{
		int v=ch[u][w];
		if (deep[u]+1==deep[v]) pa[np]=v;
		else
		{
			int nv=newnode(deep[u]+1);
			memcpy(ch[nv],ch[v],sizeof(ch[v]));
			pa[nv]=pa[v]; pa[v]=pa[np]=nv;
			while(u&&ch[u][w]==v) ch[u][w]=nv,u=pa[u];
		}
	}
	last=np;
}
int sum[N],stk[N];
void topsort()
{
	for (int i=0;i<=deep[last];i++) sum[i]=0;
	for (int i=1;i<=tot;i++) sum[deep[i]]++;
	for (int i=1;i<=deep[last];i++) sum[i]+=sum[i-1];
	for (int i=1;i<=tot;i++) stk[sum[deep[i]]--]=i;
	for (int i=tot;i>=2;i--) cnt[pa[stk[i]]]+=cnt[stk[i]];
}
