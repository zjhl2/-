#include<bits/stdc++.h>
using namespace std;

const int N=1005;

int clr[N][N];
int ga[N][N],gb[N][N];
int cnt;
void dfs(int u,int p,int c1,int c2)
{
	if (u==0)
	{
		swap(gb[p][c1],gb[p][c2]);
		return;
	}
	int v=ga[u][c2];
	if (v) dfs(gb[v][c1],v,c1,c2);
	swap(ga[u][c1],ga[u][c2]);
	swap(gb[p][c1],gb[p][c2]);
	clr[u][v]=c1;
	clr[u][p]=c2;
}

int mx[N*100],my[N*100];
int main()
{
	int a,b,m; scanf("%d%d%d",&a,&b,&m);
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		int x,y; scanf("%d%d",&x,&y);  mx[i]=x; my[i]=y;
		int c1=1;
		while(ga[x][c1]) c1++;
		int c2=1;
		while(gb[y][c2]) c2++;
		if (c1!=c2) dfs(gb[y][c1],y,c1,c2);
		ga[x][c1]=y; gb[y][c1]=x;
		clr[x][y]=c1;
		ans=max(ans,c1);
		ans=max(ans,c2);
	}
	printf("%d\n",ans);
	for (int i=1;i<=m;i++) printf("%d ",clr[mx[i]][my[i]]);
}
/*

http://codeforces.com/contest/600/problem/F
*/
